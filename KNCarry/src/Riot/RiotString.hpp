#pragma once
#include <cstdint>
#include <string>

class RiotString
{
private:
	char Content[0x10] = {}; 
	uint8_t Size = 0; // 0x10
    uint8_t MaxContentLength = 0; // 0x18
public:
    char* Get()
    {
        return this->Content;

        return this->MaxContentLength == 31
            ? *reinterpret_cast<char**>(this->Content)
            : this->Content;
    }

	explicit operator const char*()
    {
        return this->Get();
    }

	explicit operator std::string()
    {
        return std::string{this->Get()};
    }
};
