#include "MemoyScanner.hpp"
#include "../../Patchables/Offsets.hpp"

namespace mem
{
	char* ScanBasic(char* pattern, char* mask, char* begin, intptr_t size)
	{
		intptr_t patternLen = strlen(mask);

		for (int i = 0; i < size; i++)
		{
			bool found = true;
			for (int j = 0; j < patternLen; j++)
			{
				if (mask[j] != '?' && pattern[j] != *(char*)((intptr_t)begin + i + j))
				{
					found = false;
					break;
				}
			}
			if (found)
			{
				return (begin + i);
			}
		}
		return nullptr;
	}

	char* ScanInternal(char* pattern, char* mask, char* begin, intptr_t size)
	{
		char* match{ nullptr };
		MEMORY_BASIC_INFORMATION mbi{};

		for (char* curr = begin; curr < begin + size; curr += mbi.RegionSize)
		{
			if (!VirtualQuery(curr, &mbi, sizeof(mbi)) || mbi.State != MEM_COMMIT || mbi.Protect == PAGE_NOACCESS) continue;

			match = ScanBasic(pattern, mask, curr, mbi.RegionSize);

			if (match != nullptr)
			{
				break;
			}
		}
		return match;
	}

	char* ScanModInternal(char* pattern, char* mask, char* moduleBase)
	{
		char* match = ScanInternal(pattern, mask, moduleBase, Offsets::MODULE_INFO.SizeOfImage);

		return match;
	}
}