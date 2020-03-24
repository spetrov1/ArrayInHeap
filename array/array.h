#pragma once

/// Ordinary array allocated in heap
template <typename Type>
class array
{
private:
	Type* buffer; /// array storage
	
	size_t usedCapacity; /// Number of pushed elements in array

	size_t capacity; /// Allocated memory for buffer

	void copy(const array&);
	void deleteDynamicMemory();

public:

	// array(T* initValues);

	array(size_t _capacity = 10);
	array(const array&);
	array& operator=(const array&);
	~array();

	void fill(const Type& initElem);
	bool isEmpty() const;
	size_t size() const;
	
	/*
	void push_back(T);
	T& back() const;
	const T& back() const;

	T& operator[](size_t index); // const ?
	const T& operator[](size_t index) const;

	T& at(size_t index) const;
	const T& at(size_t index) const;
	*/

	// TODO operator ==
};

/// Clone other array elements into our array \n
/// Used in operator= and copy constructor \n
/// \warning std::exception is thrown if ! (this.capacity < other.size)
template <typename T>
void array<T>::copy(const array& other) {
	// TODO
}


/// deletes storage of array
template <typename T>
void array<T>::deleteDynamicMemory() {
	delete[] buffer;
}


/// \param capacity to be used for storage. \n
///
/// Used for memory allocation for the buffer
template <typename T>
array<T>::array(size_t capacity) : capacity(capacity) {}


// ? Something like cross-reference to copy(const T&) documentation ?
/// \warning std::exception is thrown if ! (this.capacity < other.size)
template <typename T>
array<T>::array(const array& other) {
	copy(other);
}


/// \warning std::exception is thrown if ! (this.capacity < other.size)
template <typename T>
array<T>& array<T>::operator=(const array& other) {
	if (this != &other) {
		deleteDynamicMemory();
		copy(other);
	}
	return *this;
}


/// Deletes allocated memory for storage(buffer)
template <typename T>
array<T>::~array() {
	deleteDynamicMemory();
}


/// TODO
/// TODO
/// TODO
template <typename T>
void array<T>::fill(const T& initElem) {
	/// TODO
}


/// TODO
/// TODO
/// TODO
template <typename T>
bool array<T>::isEmpty() const {
	return usedCapacity == 0;
}


/// TODO
/// TODO
/// TODO
template <typename T>
size_t array<T>::size() const {
	return usedCapacity;
}
