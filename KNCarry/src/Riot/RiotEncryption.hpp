#pragma once

#include <cstdint>

#pragma pack(push, 4)
template <typename T>
class RiotEncryption {
    bool XorKeyWasInit{ false }; 
    std::uint8_t BytesXorCount = 0; 
    std::uint8_t BytesXorCount8 = 0;
    T XorKey;
    std::uint8_t ValueIndex{0};
    T ValuesTable[4];

public:
    T Decrypt() noexcept {
        if (XorKeyWasInit != 1) return 0;

        auto xoredValue{ ValuesTable[ValueIndex] };
        auto xorKeyValue{ XorKey };

        {
	        const auto* xorValuePtr{ reinterpret_cast<std::uint32_t*>(&xorKeyValue) };
            for (auto i{ 0u }; i < BytesXorCount; i++)
                *(reinterpret_cast<std::uint32_t*>(&xoredValue) + i) ^= ~xorValuePtr[i];
        }

        {
	        const auto* xorValuePtr{ reinterpret_cast<std::uint8_t*>(&xorKeyValue) };
            for (auto i{ sizeof(T) - BytesXorCount8 }; i < sizeof(T); ++i)
                *(reinterpret_cast<std::uint8_t*>(&xoredValue) + i) ^= ~xorValuePtr[i];
        }

        return xoredValue;
    }

    void Encrypt(T value) noexcept {
        if (!XorKeyWasInit) {
            if (sizeof(T) <= 2) {
                BytesXorCount8 = sizeof(T);
                BytesXorCount = 0;
            }
            else {
                BytesXorCount8 = sizeof(T) % 4;
                BytesXorCount = (sizeof(T) - BytesXorCount8) / 4;
            }

            auto key{ ::__rdtsc() };
            auto keyIndex{ 0 };

            for (auto i{ 0u }; i < sizeof(T); i++) {
                *(reinterpret_cast<std::uint8_t*>(&XorKey) + i) = *(reinterpret_cast<std::uint8_t*>(&key) + keyIndex++);

                if (keyIndex == 8) {
                    key = ::__rdtsc();
                    keyIndex = 0;
                }
            }

            ValueIndex = 0;
            XorKeyWasInit = true;
        }

        auto xoredValue{ value };
        auto xorKeyValue{ XorKey };

        {
            auto* xorValuePtr{ reinterpret_cast<std::uint32_t*>(&xorKeyValue) };
            for (auto i{ 0u }; i < BytesXorCount; i++)
                *(reinterpret_cast<std::uint32_t*>(&xoredValue) + i) ^= ~xorValuePtr[i];
        }

        {
            auto* xorValuePtr{ reinterpret_cast<std::uint8_t*>(&xorKeyValue) };

            for (auto i{ sizeof(T) - BytesXorCount8 }; i < sizeof(T); ++i)
                *(reinterpret_cast<std::uint8_t*>(&xoredValue) + i) ^= ~xorValuePtr[i];
        }

        auto newValueIndex{ std::uint8_t(ValueIndex + 1) & 3 };
        ValuesTable[newValueIndex] = xoredValue;
        ValueIndex = newValueIndex;
    }
};
#pragma pack(pop)