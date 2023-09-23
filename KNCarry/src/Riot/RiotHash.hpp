#pragma once
#include <cstdint>

constexpr std::uint32_t FNV1A32HashCI(char const* const szString, const std::uint32_t iHash = 0x811C9DC5) {
	return '\0' == szString[0] ? iHash : FNV1A32HashCI(&szString[1], (((szString[0] >= 'A' && szString[0] <= 'Z') ? szString[0] + ('a' - 'A') : szString[0]) ^ iHash) * 0x1000193);
}

constexpr std::uint32_t FNV132HashCI(char const* const szString, const std::uint32_t iHash = 0x811C9DC5) {
	return '\0' == szString[0] ? iHash : FNV132HashCI(&szString[1], (iHash * 0x1000193) ^ ((szString[0] >= 'A' && szString[0] <= 'Z') ? szString[0] + ('a' - 'A') : szString[0]));
}

constexpr std::uint32_t FNV1A32Salt(const std::uint32_t iStartHash, const std::uint32_t iSalt) {
	std::uint32_t iHash = iStartHash;

	for (size_t iIndex = 0; iIndex < 4; iIndex++) {
		iHash ^= reinterpret_cast<const uint8_t*>(&iSalt)[iIndex];
		iHash *= 0x1000193;
	}

	return iHash;
}

constexpr std::uint32_t SDBM32HashCI(char const* const szString, const std::uint32_t iHash = 0) {
	return '\0' == szString[0] ? iHash : SDBM32HashCI(&szString[1], ((szString[0] >= 'A' && szString[0] <= 'Z') ? szString[0] + ('a' - 'A') : szString[0]) + (iHash << 6) + (iHash << 16) - iHash);
}

constexpr std::uint32_t ELF32HashCI(char const* const szString, const  std::uint32_t iHash = 0x0) {
	std::uint32_t iValue = (16 * iHash + ((szString[0] >= 'A' && szString[0] <= 'Z') ? (szString[0] - 'A' + 'a') : szString[0]));
	return '\0' == szString[0] ? iHash : ELF32HashCI(&szString[1], (iValue & 0xF0000000) ? (iValue & 0xF0000000 ^ ((iValue & 0xF0000000) >> 24) ^ iValue) : iValue);
}

#define FNV1A32CI(s) std::integral_constant<std::uint32_t, FNV1A32HashCI(s)>::value
#define FNV132CI(s) std::integral_constant<std::uint32_t, FNV132HashCI(s)>::value
#define SDBM32CI(s) std::integral_constant<std::uint32_t, SDBM32HashCI(s)>::value
#define ELF32CI(s) std::integral_constant<uint32_t, ELF32HashCI(s)>::value
