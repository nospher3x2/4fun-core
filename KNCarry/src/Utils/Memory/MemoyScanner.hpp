#pragma once
#include <Windows.h>

class MemoryScanner
{
public:
	static void* ScanModInternal(const char* pattern, const char* mask, char* baseAddress);
private:
	static char* ScanInternal(const char* pattern, const char* mask, char* begin, size_t size);
	static char* ScanBasic(const char* pattern, const char* mask, char* begin, size_t size);
};
