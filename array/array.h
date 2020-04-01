#pragma once

#include <cassert>
#include <iostream>
#include "ref_bit.h"

// ASK
// typedef uint8_t byte


/// Ordinary non-resizable array allocated in heap
template <typename T>
class array
{
protected:
	T* buffer; /// array storage
	
	size_t usedCapacity; /// Number of pushed elements in array

	size_t capacity; /// Allocated memory for buffer


	/// Copy given buffer into this.buffer \n
	/// Used in operator= and copy constructor \n
	/// \throws X if T::operator= throws X while copying
	/// TODO Error T must be a class or namespace (T::operator=) ?
	void copyBuffer(T* _buffer, size_t _bufferSize) // noexcept (noexcept(T::operator=))
	{
		for (size_t i = 0; i < _bufferSize; ++i)
			buffer[i] = _buffer[i]; /// may throw X exception
	}


	/// deletes storage of array
	void deleteDynamicMemory()
	{
		delete[] buffer;
	}

public:

	// array(T* initValues);


	/// \param capacity to be used for storage. \n
	///
	/// Used for memory allocation for the buffer
	///
	/// \throws std::bad_alloc if memory allocation fails
	array(size_t _capacity = 10)
	{
		if (_capacity == 0)
			throw std::invalid_argument("Invalid argument to array constructor");

		buffer = new T[_capacity]; // may throw bad_alloc

		capacity = _capacity;
	}



	/// Just an ordinary copy consturctor
	///
	/// \throws std::bad_alloc if memory allocation fails
	/// \throws X if T::operator= throws X while copying
	array(const array& other) {
		buffer = new T[other.capacity]; // may throw bad_alloc

		try {
			copyBuffer(other.buffer, other.usedCapacity); // may throw while coping..
		}
		catch (...) {
			delete[] buffer;
			buffer = nullptr;
			throw;
		}
		capacity = other.capacity;
		usedCapacity = other.usedCapacity;
	}


	/// Copy all the elems of given array into this.array \n
	/// After operator= capacities of objects remain different if they were different
	/// \warning std::exception is thrown if (this.capacity < other.size)
	array& operator=(const array& other) 
	{
		if (this->capacity < other.size()) {
			throw std::exception();
		}
		if (this != &other) {
			try {
				copyBuffer(other.buffer, other.size()); // may throw while coping
			}
			catch (...) {
				delete[] buffer;
				buffer = nullptr;
				throw; // TODO throw with better message
			}
			usedCapacity = other.usedCapacity;
		}
		return *this;
	}


	/// Deletes allocated memory for storage(buffer)
	~array() noexcept {
		deleteDynamicMemory();
	}


	/// Fill the container with the specified value initElem \n
	/// \param initElem - the value to assign to all the elements
	/// \throws X if T::operator= throws X while copying
	void fill(const T& initElem)
	{
		for (size_t i = 0; i < capacity; ++i)
			buffer[i] = initElem;

		usedCapacity = capacity;
	}



	/// Checks whether array is empty
	bool isEmpty() const noexcept {
		return usedCapacity == 0;
	}



	/// Checks if array is full
	bool isFull() const {
		return usedCapacity == capacity;
	}



	/// \return number of already pushed elements in the array
	size_t size() const noexcept {
		return usedCapacity;
	}
	

	
	/// Adds element to the end of array \n
	/// \param newElem to be inserted in array
	/// \exception if container is full, exception is throwed
	void push_back(const T& newElem)
	{
		if (isFull())
			throw std::exception();

		buffer[usedCapacity++] = newElem;
	}



	/// Returns and removes last element
	/// \return Reference to last element
	/// \exception If there is no such element is throwed exception
	T& pop_back()
	{
		if (isEmpty())
			throw std::exception();
		return buffer[--usedCapacity];
	}



	/// \return Reference to the last element
	///
	/// \exception If there is no such element, exception is throwed
	T& back()
	{
		if (isEmpty())
			throw std::exception();
		return buffer[usedCapacity - 1];
	}



	/// Working for constant instances of array
	/// \return Reference to the last element
	///
	/// \exception If there is no such element, exception is throwed
	const T& back() const
	{
		if (isEmpty())
			throw std::exception();
		return buffer[usedCapacity - 1];
	}



	/// \param index - position of the element to return
	/// \return Reference to the element specified by index position
	/// \warning Passing invalid argument, the behaviour is undefined
	T& operator[](size_t index) noexcept
	{
		assert(index < usedCapacity);

		return buffer[index];
	}



	/// Working for constant instances of array
	/// \param index - position of the element to return
	/// \return Reference to the element specified by index position
	/// \warning Passing invalid argument, the behaviour is undefined
	const T& operator[](size_t index) const noexcept
	{
		assert(index < usedCapacity);

		return buffer[index];
	}



	/// \return Reference to the specified element by index position
	/// \exception Accessing index which is out of range of array container, 
	///               exception out_of_range is throwed
	T& at(size_t index)
	{
		if (index >= usedCapacity)
			throw std::out_of_range("There is no such element at this index in array");
		return buffer[index];
	}



	/// 
	/// \return Reference to the specified element by index position
	/// \exception Accessing index which is out of range of array container, 
	///               exception out_of_range is throwed
	const T& at(size_t index) const
	{
		if (index >= size)
			throw std::out_of_range("There is no such element at this index in array");
		return buffer[index];
	}

	

	/// \param other - array to compare to
	/// \return True if for each i this[i] == other[i] \n
	/// this.capacity != other.capacity is allowed
	/// \throws X if T::operator== throws X while comparing
	bool operator== (const array& other) const
	{
		if (usedCapacity != other.usedCapacity)
			return false;
		for (size_t i = 0; i < usedCapacity; ++i) {
			if (! (buffer[i] == other.buffer[i]) ) // may throw
				return false;
		}

		return true;
	}

};




/// Specialization of array
/// Bool version of template array
template <>
class array<bool> : public array<byte> {

public:

	/// Allocate (capacity / 8) trying to use every bit of a byte
	array(size_t _capacity = 10) : 
		array<byte>(ceil(_capacity / 8.0)) /// allocating appropriate number of bytes
	{
		size_t numberOfBytesInArray = ceil(_capacity / 8.0);
		for (size_t i = 0; i < numberOfBytesInArray; ++i)
			buffer[i] = 0;
		capacity = _capacity;
	}



	// ASK Is there have to be noexcept
	//		Because push_back may throw but the way we implemented the function
	//			makes it imposible	
	/// Fill all the capacity in array with the given parameter
	/// \param elemToFillWith is the element used to fill the array with
	void fill(const bool& elemToFillWith) noexcept {
		usedCapacity = 0; // clear out array
		while (!isFull()) {
			push_back(elemToFillWith);
		}
	}



	/// Adds element to the end of array \n
	/// \param newElem to be inserted in array
	/// \exception if container is full, exception is throwed
	void push_back(const bool& newElem) {
		if (isFull())
			throw std::exception("Array is full !!!");

		size_t byteIndex = usedCapacity / 8;
		size_t numberOfBitInByte = usedCapacity % 8;

		if (newElem == 1) // or true
			setNthBit(buffer[byteIndex], numberOfBitInByte);
		++usedCapacity;
	}



	/// Returns and removes last element
	/// \return Reference to last element
	/// \exception If there is no such element is throwed exception
	ref_bit pop_back() {
		if (isEmpty())
			throw std::exception();
		size_t lastElemIndex = usedCapacity - 1;
		ref_bit elemToReturn = this->operator[](lastElemIndex);
		--usedCapacity;

		return elemToReturn;
	}


	/// \return Reference to the last element
	///
	/// \exception If there is no such element, exception is throwed
	ref_bit back() {
		if (isEmpty())
			throw std::exception();
		size_t lastElemIndex = usedCapacity - 1;

		return operator[](lastElemIndex);
	}



	/// \param index - position of the element(bit) to return
	/// \return ref_bit struct which is implemented to be reference 
	///		to the queried bit specified by index parameter
	/// \warning Passing invalid argument, the behaviour is undefined
	ref_bit operator[](size_t index) noexcept {
		assert(index < usedCapacity);

		size_t byteIndexInArray = index / 8;
		uint8_t bitIndexInByte = index % 8;

		return ref_bit(buffer[byteIndexInArray], bitIndexInByte);
	}



	/// \return Reference to the specified element by index position
	/// \exception Accessing index which is out of range of array container, 
	///               exception out_of_range is throwed
	ref_bit at(size_t index) {
		if (index >= usedCapacity)
			throw std::out_of_range("Queried index in bool array is invalid");
		
		return this->operator[](index);
	}





	// TODO back(Constant and non-constant)
	// TODO operator[] (Constant)
	// TODO at(Constant and non-constant)

};