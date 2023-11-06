#include "MemoyScanner.hpp"
#include <Psapi.h>

void* MemoryScanner::ScanModInternal(const char* pattern, const char* mask, char* baseAddress)
{
	MODULEINFO module{};
	if (!GetModuleInformation(GetCurrentProcess(), reinterpret_cast<HMODULE>(baseAddress), &module, sizeof(MODULEINFO)))
		return nullptr;

	char* match = MemoryScanner::ScanInternal(pattern, mask, baseAddress, module.SizeOfImage);
	return match;
}

char* MemoryScanner::ScanInternal(const char* pattern, const char* mask, char* begin, const size_t size)
{
	MEMORY_BASIC_INFORMATION mbi{};

	for (char* curr = begin; curr < begin + size; curr += mbi.RegionSize)
	{
		if (!VirtualQuery(curr, &mbi, sizeof mbi))
			continue;

		if (mbi.State != MEM_COMMIT || mbi.Protect == PAGE_NOACCESS)
			continue;

		char* match = MemoryScanner::ScanBasic(pattern, mask, curr, mbi.RegionSize);
		if (match)
			return match;
	}

	return nullptr;
}

char* MemoryScanner::ScanBasic(const char* pattern, const char* mask, char* begin, const size_t size)
{
	const size_t patternLen = strlen(mask);
	for (size_t i = 0; i < size; i++)
	{
		bool found = true;
		for (size_t j = 0; j < patternLen; j++)
		{
			if (mask[j] != '?' && pattern[j] != *(begin + i + j))
			{
				found = false;
				break;
			}
		}

		if (found)
			return begin + i;
	}

	return nullptr;
}

