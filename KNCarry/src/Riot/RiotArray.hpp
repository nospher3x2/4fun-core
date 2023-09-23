#pragma once
#include <cstdint>
#include "../Patchables/Offsets.hpp"

template<typename T>
class RiotArray
{
public:
	union
	{
		DEFINE_MEMBER_N(T* List, 0x8);
		DEFINE_MEMBER_N(uint32_t Size, 0x10);
	};

	const T& front() {
		return this->List[0];
	}

	const T& back() {
		return this->List[this->Size - 1];
	}

	T* begin() {
		return this->List;
	}

	T* end() {
		return this->List + this->Size;
	}

	const T& at(std::size_t index) {
		return this->List[index];
	}

	const T& operator[](std::size_t index) {
		return this->List[index];
	}
};