#pragma once
#include <Windows.h>

namespace mem
{
	char* ScanModInternal(char* pattern, char* mask, char* moduleBase);
}