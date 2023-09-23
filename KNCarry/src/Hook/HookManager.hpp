#pragma once
#include <cstdint>
#include <string>
#include <Zydis/Zydis.h>
#include <vector>
#include <Windows.h>
#include <TlHelp32.h>
#include "Syscall/Syscall.hpp"


typedef struct _OBJECT_ATTRIBUTES {
	ULONG Length;
	HANDLE RootDirectory;
	PUNICODE_STRING ObjectName;
	ULONG Attributes;
	PVOID SecurityDescriptor;        // Points to type SECURITY_DESCRIPTOR
	PVOID SecurityQualityOfService;  // Points to type SECURITY_QUALITY_OF_SERVICE
} OBJECT_ATTRIBUTES;

#define InitializeObjectAttributes( p, n, a, r, s ) { \
    (p)->Length = sizeof( OBJECT_ATTRIBUTES );          \
    (p)->RootDirectory = r;                             \
    (p)->Attributes = a;                                \
    (p)->ObjectName = n;                                \
    (p)->SecurityDescriptor = s;                        \
    (p)->SecurityQualityOfService = NULL;               \
    }


typedef struct _CLIENT_ID
{
	HANDLE UniqueProcess;
	HANDLE UniqueThread;
} CLIENT_ID;

#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)

class HookManager
{
	
	
	struct HWBPHook
	{
		uintptr_t FunctionAddress;
		uintptr_t TrampolineAddress;
		uintptr_t HookAddress;
		uint8_t Index;
	};

	static inline uintptr_t DR0{ 0 };
	static inline uintptr_t DR1{ 0 };
	static inline uintptr_t DR2{ 0 };
	static inline uintptr_t DR3{ 0 };
	static inline uintptr_t DR7{ 0 };

	static inline void* VEH_Handle = nullptr;
	static inline void* VCH_Handle = nullptr;


	static inline std::vector<HWBPHook> HWBPHooks = {};

	static void AddHook(const uintptr_t address, const uintptr_t callback, size_t size, const uint8_t index)
	{
		if (HWBPHooks.empty())
		{
			VEH_Handle = AddVectoredExceptionHandler(1, [](PEXCEPTION_POINTERS pExceptionInfo) -> LONG
				{
					pExceptionInfo->ContextRecord->Dr0 = 0;
					pExceptionInfo->ContextRecord->Dr1 = 0;
					pExceptionInfo->ContextRecord->Dr2 = 0;
					pExceptionInfo->ContextRecord->Dr3 = 0;
					pExceptionInfo->ContextRecord->Dr6 = 0;
					pExceptionInfo->ContextRecord->Dr7 = 0;

					if (pExceptionInfo->ExceptionRecord->ExceptionCode == STATUS_SINGLE_STEP)
					{
						for (const HWBPHook hs : HWBPHooks)
						{
							if (pExceptionInfo->ContextRecord->Rip == hs.FunctionAddress)
							{
								pExceptionInfo->ContextRecord->Dr6 = 0;
								pExceptionInfo->ContextRecord->Rip = hs.HookAddress;
							}
						}

						return EXCEPTION_CONTINUE_EXECUTION;
					}

					return EXCEPTION_CONTINUE_SEARCH;
				}
			);

			VCH_Handle = AddVectoredContinueHandler(1, [](EXCEPTION_POINTERS* pExceptionInfo) -> LONG
				{
					pExceptionInfo->ContextRecord->Dr0 = DR0;
					pExceptionInfo->ContextRecord->Dr1 = DR1;
					pExceptionInfo->ContextRecord->Dr2 = DR2;
					pExceptionInfo->ContextRecord->Dr3 = DR3;
					pExceptionInfo->ContextRecord->Dr7 = DR7;
					return EXCEPTION_CONTINUE_EXECUTION;
				}
			);

			if (GetSystemDEPPolicy() != DEP_SYSTEM_POLICY_TYPE::DEPPolicyAlwaysOff)
				SetProcessDEPPolicy(PROCESS_DEP_ENABLE);
		}

		for (const auto& hook : HWBPHooks)
		{
			if (hook.FunctionAddress == address || hook.Index == index)
			{
				return;
			}
		}

		if (!VEH_Handle)
			return;

		return;


		const HWBPHook hook{
			.FunctionAddress = address,
			.HookAddress = callback,
			.Index = index
		};

		HWBPHooks.push_back(hook);

		const HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
		if (!hThreadSnap)
			return;

		THREADENTRY32 te32;
		te32.dwSize = sizeof(THREADENTRY32);
		if (!Thread32First(hThreadSnap, &te32))
			CloseHandle(hThreadSnap);

		do
		{
			if (te32.th32OwnerProcessID == GetCurrentProcessId() && te32.th32ThreadID != GetCurrentThreadId())
			{
				OBJECT_ATTRIBUTES objectAttributes;
				InitializeObjectAttributes(
					&objectAttributes,
					NULL, 
					NULL, 
					NULL,
					NULL
				)

				CLIENT_ID clientId;
				clientId.UniqueProcess = reinterpret_cast<void*>(te32.th32OwnerProcessID);
				clientId.UniqueThread = reinterpret_cast<void*>(te32.th32ThreadID);

				HANDLE threadHandle = nullptr;
				const NTSTATUS res = syscall_direct::create_syscall<NTSTATUS>(
					"RtlInterlockedCompareExchange64", 
					&threadHandle, 
					THREAD_GET_CONTEXT | THREAD_SET_CONTEXT | THREAD_SUSPEND_RESUME,
					&objectAttributes, 
					&clientId
				);

				if (!NT_SUCCESS(res))
					continue;

				if (!threadHandle)
					continue;

				CONTEXT context;
				context.ContextFlags = CONTEXT_DEBUG_REGISTERS;

				if (NT_SUCCESS(
					syscall_direct::create_syscall<NTSTATUS>("RtlInterlockedCompareExchange64", threadHandle, &context)))
				{
					if (te32.th32ThreadID != GetCurrentThreadId())
					{
						syscall_direct::create_syscall<NTSTATUS>("RtlInterlockedCompareExchange64", threadHandle, NULL);
					}

					bool isInvalidReg = false;
					switch (index)
					{
					case 0:
						context.Dr0 = address;
						DR0 = address;
						break;
					case 1:
						context.Dr1 = address;
						DR1 = address;
						break;
					case 2:
						context.Dr2 = address;
						DR2 = address;
						break;
					case 3:
						context.Dr3 = address;
						DR3 = address;
						break;
					default:
						isInvalidReg = true;
						break;
					}

					if (!isInvalidReg)
					{
						context.Dr7 &= ~(3ULL << (16 + 4 * index));
						context.Dr7 &= ~(3ULL << (18 + 4 * index));
						context.Dr7 |= 1ULL << (2 * index);
						DR7 = context.Dr7;

						syscall_direct::create_syscall<NTSTATUS>(
							"RtlInterlockedCompareExchange64", 
							threadHandle, 
							&context
						);
					}

					if (te32.th32ThreadID != GetCurrentThreadId())
					{
						syscall_direct::create_syscall<NTSTATUS>(
							"RtlInterlockedCompareExchange64", 
							threadHandle, 
							NULL
						);
					}

					CloseHandle(threadHandle);
				}
			}
		} while (Thread32Next(hThreadSnap, &te32));
		CloseHandle(hThreadSnap);

	}

	bool SysVirtualProtect(uintptr_t lpAddress, size_t* dwSize, uintptr_t flNewProtect, uintptr_t lpflOldProtect)
	{
		
	}

	void FixFunctionReallocation(uintptr_t OldFnAddress, uintptr_t OldFnAddressEnd, uintptr_t NewFnAddress, size_t size, size_t _offset)
	{
		ZydisDecoder decoder;
		ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);

		ZydisFormatter formatter;
		ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL);

		ZyanU64 runtime_address = OldFnAddress + _offset;
		ZyanUSize offset = _offset;

		const ZyanUSize length = size;
		ZydisDecodedInstruction instruction;
		int fixedAddressesCount = 0;

		ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT];
		while (ZYAN_SUCCESS(ZydisDecoderDecodeFull(&decoder, (void*)(NewFnAddress + offset), length - offset, &instruction, operands)))
		{
			char buffer[256];
			ZydisFormatterFormatInstruction(
				&formatter, 
				&instruction, 
				operands, 
				instruction.operand_count_visible,
				buffer, 
				sizeof(buffer),
				runtime_address, 
				ZYAN_NULL
			);

			std::string mnemonic(buffer);
			if (mnemonic.find("call 0x") != std::string::npos) {

				uintptr_t originalCall = 0;
				{
					ZydisDecoder decoder1;
					ZydisDecoderInit(
						&decoder1, 
						ZYDIS_MACHINE_MODE_LONG_64, 
						ZYDIS_STACK_WIDTH_64
					);

					ZydisFormatter formatter1;
					ZydisFormatterInit(&formatter1, ZYDIS_FORMATTER_STYLE_INTEL);

					const ZyanUSize length = size;
					ZydisDecodedInstruction instruction1;
					{
						if (ZYAN_SUCCESS(
							ZydisDecoderDecodeFull(
								&decoder1,
								(void*)(OldFnAddress + offset),
								length - offset, 
								&instruction1,
								operands
							)
						))
						{
							char buffer1[256];
							ZydisFormatterFormatInstruction(
								&formatter1, 
								&instruction1,
								operands,
								instruction.operand_count_visible, 
								buffer1,
								sizeof(buffer1), 
								OldFnAddress + offset, 
								ZYAN_NULL
							);

							std::string mnemonic1(buffer1);
							if (mnemonic1.find("call 0x") != std::string::npos) {
								originalCall = std::strtoul((mnemonic1.substr(5, 10)).c_str(), NULL, 16);
							}
						}
					}
				}
				/////////////////////////////////////////////
				// END GET ORIGINAL OFFSET FROM ORIGINAL FUNCTION
				/////////////////////////////////////////////
				/////////////////////////////////////////////
				// APPLY RELOCATION FIXES
				/////////////////////////////////////////////
				{
					uintptr_t calc1 = (runtime_address - originalCall + 4);
					uintptr_t calc = 0xFFFFFFFF - calc1;
					*(uintptr_t*)(runtime_address + 1) = calc;

					if (ZYAN_SUCCESS(
						ZydisDecoderDecodeFull(
							&decoder, 
							(void*)(NewFnAddress + offset), 
							length - offset, 
							&instruction,
							operands
						)
					))
					{
						char buffer[256];
						ZydisFormatterFormatInstruction(
							&formatter,
							&instruction,
							operands,
							instruction.operand_count_visible,
							buffer,
							sizeof(buffer),
							runtime_address,
							ZYAN_NULL
						);

						std::string mnemonic(buffer);
						//////////////////////////////////////////////////////////////////////////////////////////
						// CHECK IF THE RELOCATED FIXES HAVE INSTRUCTIONS THAT CALL ORIGINAL. THEN CORRECT IT
						//////////////////////////////////////////////////////////////////////////////////////////
						{
							uintptr_t hex = std::strtoul((mnemonic.substr(5, 10)).c_str(), NULL, 16);
							if ((hex >= OldFnAddress) && (hex <= OldFnAddressEnd)) {
								uintptr_t calc1 = (runtime_address - hex + 4);
								uintptr_t calc = 0xFFFFFFFF - calc1;
								*(uintptr_t*)(runtime_address + 1) = calc;

								if (ZYAN_SUCCESS(ZydisDecoderDecodeFull(&decoder, (void*)(NewFnAddress + offset), length - offset, &instruction, {}))) {

									char buffer[256];
									ZydisFormatterFormatInstruction(
										&formatter,
										&instruction,
										operands,
										instruction.operand_count_visible,
										buffer,
										sizeof(buffer),
										runtime_address,
										ZYAN_NULL
									);
									std::string mnemonic(buffer);
								}

							}
						}
						//////////////////////////////////////////////////////////////////////////////////////////
						// END CHECK IF THE RELOCATED FIXES HAVE INSTRUCTIONS THAT CALL ORIGINAL. THEN CORRECT IT
						//////////////////////////////////////////////////////////////////////////////////////////
					}
				}
				/////////////////////////////////////////////
				// END APPLY RELOCATION FIXES
				/////////////////////////////////////////////

				fixedAddressesCount++;
			}
			else if (mnemonic.find("int3") != std::string::npos) {
				*(unsigned char*)(NewFnAddress + offset) = 0x90;
				fixedAddressesCount++;
			}
			else if ((mnemonic.find("jmp 0x") != std::string::npos) && (*(unsigned char*)(runtime_address) == 0xe9)) {

				uintptr_t originalCall = 0;
				/////////////////////////////////////////////
				// GET ORIGINAL OFFSET FROM ORIGINAL FUNCTION
				/////////////////////////////////////////////
				{
					// Initialize decoder context
					ZydisDecoder decoder1;
					ZydisDecoderInit(&decoder1, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);

					// Initialize formatter. Only required when you actually plan to do instruction
					// formatting ("disassembling"), like we do here
					ZydisFormatter formatter1;
					ZydisFormatterInit(&formatter1, ZYDIS_FORMATTER_STYLE_INTEL);

					// Loop over the instructions in our buffer.
					// The runtime-address (instruction pointer) is chosen arbitrary here in order to better
					// visualize relative addressing
					const ZyanUSize length = size;
					ZydisDecodedInstruction instruction1;
					{
						if (ZYAN_SUCCESS(
							ZydisDecoderDecodeFull(
								&decoder1, 
								(void*)(OldFnAddress + offset),
								length - offset, 
								&instruction1,
								operands
							)
						)) 
						{
							char buffer1[256];
							ZydisFormatterFormatInstruction(
								&formatter1, 
								&instruction1,
								operands, 
								instruction.operand_count_visible,
								buffer1, 
								sizeof(buffer1),
								OldFnAddress + offset,
								ZYAN_NULL
							);

							std::string mnemonic1(buffer1);
							if (mnemonic1.find("jmp 0x") != std::string::npos) {
								originalCall = std::strtoul((mnemonic1.substr(4, 10)).c_str(), NULL, 16);
							}
						}
					}
				}
				/////////////////////////////////////////////
				// END GET ORIGINAL OFFSET FROM ORIGINAL FUNCTION
				/////////////////////////////////////////////
				/////////////////////////////////////////////
				// APPLY RELOCATION FIXES
				/////////////////////////////////////////////
				{
					uintptr_t calcx = originalCall - (OldFnAddress + offset);
					uintptr_t calcy = calcx + (OldFnAddress + offset);
					uintptr_t calc = calcy - runtime_address - 0x5;

					*(uintptr_t*)(runtime_address + 1) = calc;

					if (ZYAN_SUCCESS(ZydisDecoderDecodeFull(&decoder, (void*)(NewFnAddress + offset), length - offset, &instruction, operands))) {

						char buffer[256];
						ZydisFormatterFormatInstruction(
							&formatter,
							&instruction,
							operands,
							instruction.operand_count_visible,
							buffer,
							sizeof(buffer),
							runtime_address,
							ZYAN_NULL
						);

						std::string mnemonic(buffer);
						//////////////////////////////////////////////////////////////////////////////////////////
						// CHECK IF THE RELOCATED FIXES HAVE INSTRUCTIONS THAT CALL ORIGINAL. THEN CORRECT IT
						//////////////////////////////////////////////////////////////////////////////////////////
						{
							uintptr_t hex = std::strtoul((mnemonic.substr(4, 10)).c_str(), NULL, 16);
							if ((hex >= OldFnAddress) && (hex <= OldFnAddressEnd)) {
								uintptr_t calc = calcx - 0x5;
								*(uintptr_t*)(runtime_address + 1) = calc;

								if (ZYAN_SUCCESS(ZydisDecoderDecodeFull(&decoder, (void*)(NewFnAddress + offset), length - offset, &instruction, operands))) {

									char buffer[256];
									ZydisFormatterFormatInstruction(
										&formatter,
										&instruction,
										operands,
										instruction.operand_count_visible,
										buffer,
										sizeof(buffer),
										runtime_address,
										ZYAN_NULL
									);

									std::string mnemonic(buffer);
								}

							}
						}
						//////////////////////////////////////////////////////////////////////////////////////////
						// END CHECK IF THE RELOCATED FIXES HAVE INSTRUCTIONS THAT CALL ORIGINAL. THEN CORRECT IT
						//////////////////////////////////////////////////////////////////////////////////////////
					}
				}
				/////////////////////////////////////////////
				// END APPLY RELOCATION FIXES
				/////////////////////////////////////////////

				fixedAddressesCount++;

			}

			offset += instruction.length;
			runtime_address += instruction.length;
		}
	}
};

