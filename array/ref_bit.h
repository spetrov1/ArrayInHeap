#pragma once

#include <iostream>


typedef uint8_t byte;

// TODO add following functions to ref_bit class as static
int getNthBit(byte num, uint8_t n);
void printByte(byte x);
void setNthBit(byte& bitArray, uint8_t n);
void dropNthBit(byte& bitArray, uint8_t n);



// ASK
// Not used in this project but just for practice
// TODO template <typename T, size_t SIZE>
template <typename T, size_t size>
size_t getSize(T(&arr)[size]) {
	return size;
}



/// Struct used as a reference to a bit
/// It is used in array<bool> to ref difference bits
struct ref_bit {
private:
	uint8_t num_of_bit; /// Number of the bit in the byte(data)
	byte* data; /// The byte in which referenced bit is

public:

	ref_bit(byte& _data, uint8_t& num) : data(&_data), num_of_bit(num) {}



	// ? Copy constructor which calls operator=



	/// If bit is 0, then it is fliped to 1
	/// If bit is 1, then it is fliped to 0
	void flip() {
		if (getNthBit(*data, num_of_bit)) {
			dropNthBit(*data, num_of_bit);
		}
		else {
			setNthBit(*data, num_of_bit);
		}
	}



	// TODO maybe return ref_bit& or ref_bit ?
	/// Make possible to do sth like :
	///		refBit = true;
	ref_bit& operator=(const bool& value) {
		if (value) {
			setNthBit(*data, num_of_bit);
		}
		else {
			dropNthBit(*data, num_of_bit);
		}

		return *this;
	}



	ref_bit& operator=(const ref_bit& other) {
		return (*this = bool(other));
	}



	/// Casting to bool function
	operator bool() const {
		return getNthBit(*data, num_of_bit);
	}



	/// Make possible to do: 
	///		std::cout << refBitInstance;
	friend std::ostream& operator<<(std::ostream& os, const ref_bit& bit) {
		os << (bool)bit << std::endl;

		return os;
	}

};


/// \param n < 8
// ? Why not working if return byte(int8_t) or bool ?
int getNthBit(byte num, uint8_t n) {
	return (num >> n) & 1;
}


void printByte(byte x) {
	unsigned int mask = 0x80;

	while (mask > 0) {
		std::cout << ((x & mask) ? 1 : 0);
		mask = mask >> 1;
	}
	// std::cout << '\n';
}

/// If n > 7 behaviour is undefined
/// Nth bit of bitArray is set to 1
void setNthBit(byte& bitArray, uint8_t n) {
	unsigned int mask = 1;
	mask = mask << n;

	bitArray = bitArray | mask;
}



/// If n > 7 behaviour is undefined
/// Nth bit of bitArray is set to 0
void dropNthBit(byte& bitArray, uint8_t n) {
	unsigned int mask = 1;
	mask = mask << n;
	mask = ~mask;

	bitArray = bitArray & mask;
}

