#pragma once

#include <cassert>

/// Ordinary non-resizable array allocated in heap
///
/// T must be default constructible and copy assignable
template <typename T>
class array
{
private:
	T* buffer = nullptr; /// array storage
	
	size_t usedCapacity = 0; /// Number of pushed elements in array

	size_t capacity = 0; /// Allocated memory for buffer

	void copyBuffer(T* buffer, size_t size);
	void deleteDynamicMemory();

public:

	// array(T* initValues);

	array(size_t _capacity = 10);
	array(const array&);
	array& operator=(const array&);
	~array();

	void fill(const T& initElem);
	bool isEmpty() const;
	size_t size() const;
	
	
	void push_back(const T&);
	T& pop_back();
	T& back();
	const T& back() const;

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	T& at(size_t index);
	const T& at(size_t index) const;
	
	bool operator== (const array&) const;
};

/// Copy given buffer into this.buffer \n
/// 
/// Used in operator= and copy constructor \n
template <typename T>
void array<T>::copyBuffer(T* _buffer, size_t _bufferSize) noexcept (noexcept(T::operator=))
{
	for (size_t i = 0; i < _bufferSize; ++i)
		buffer[i] = _buffer[i]; /// TODO ?
}


/// deletes storage of array
template <typename T>
void array<T>::deleteDynamicMemory() noexcept {
	delete[] buffer;
}


/// \param capacity to be used for storage. \n
///
/// Used for memory allocation for the buffer
///
/// \throws std::bad_alloc if memory allocation fails
template <typename T>
array<T>::array(size_t _capacity)
{
	if (_capacity == 0)
		throw std::invalid_argument();

	buffer = new T[capacity];

	capacity = _capacity;
}


/// Just an ordinary copy consturctor
///
/// \throws std::bad_alloc if memory allocation fails
/// \throws X if T::operator= throws X while copying
template <typename T>
array<T>::array(const array& other)
{
	buffer = new T[other.capacity];

	try {
		copyBuffer(other.buffer, other.size());
	}
	catch (...) {
		delete[] buffer;
		buffer = nullptr;
		throw;
	}

	usedCapacity = other.usedCapacity;
	capacity = other.capacity;
}


/// Copy all the elems of given array into this.array \n
/// After operator= capacities of objects remain different if they were different
/// \warning std::exception is thrown if (this.capacity < other.size)
template <typename T>
array<T>& array<T>::operator=(const array& other) {

	//TODO drop this check
	if (this->capacity < other.size()) {
		throw std::exception();
	}
	if (this != &other) {
		//TODO copy to a new buffer and free memory only if succesful
		//     (strong exception safety guarantee)
		copyBuffer(other.buffer, other.size());
		
		usedCapacity = other.usedCapacity;
	}
	return *this;
}


/// Deletes allocated memory for storage(buffer)
template <typename T>
array<T>::~array() noexcept {
	deleteDynamicMemory();
}


/// Fill the container with the specified value initElem \n
/// \param initElem - the value to assign to all the elements
template <typename T>
void array<T>::fill(const T& initElem) {
	for (size_t i = 0; i < capacity; ++i)
		buffer[i] = initElem; // TODO may throw ?
	usedCapacity = capacity;
}


/// Checks whether array is empty
template <typename T>
inline bool array<T>::isEmpty() const noexcept {
	return usedCapacity == 0;
}


/// \return number of already pushed elements in the array
template <typename T>
inline size_t array<T>::size() const noexcept  {
	return usedCapacity;
}


/// Adds element to the end of array \n
/// \param newElem to be inserted in array
/// \exception if container is full, exception is throwed
template<typename T>
inline void array<T>::push_back(const T& newElem)
{
	if (usedCapacity == capacity)
		throw std::exception();

	buffer[usedCapacity++] = newElem;
}


/// Returns and removes last element
/// \return Reference to last element
/// \exception If there is no such element is throwed exception
template<typename T>
inline T& array<T>::pop_back()
{
	if (isEmpty())
		throw std::exception();
	return buffer[--usedCapacity];
}


/// \return Reference to the last element
///
/// \exception If there is no such element, exception is throwed
template<typename T>
inline T& array<T>::back()
{
	if (isEmpty())
		throw std::exception();
	return buffer[usedCapacity - 1];
}


/// Working for constant instances of array
/// \return Reference to the last element
///
/// \exception If there is no such element, exception is throwed
template<typename T>
inline const T& array<T>::back() const
{
	if (isEmpty())
		throw std::exception();
	return buffer[usedCapacity - 1];
}


/// \param index - position of the element to return
/// \return Reference to the element specified by index position
/// \warning Passing invalid argument, the behaviour is undefined
template<typename T>
inline T& array<T>::operator[](size_t index) noexcept
{
	assert(index < usedCapacity);

	return buffer[index];
}


/// Working for constant instances of array
/// \param index - position of the element to return
/// \return Reference to the element specified by index position
/// \warning Passing invalid argument, the behaviour is undefined
template<typename T>
inline const T& array<T>::operator[](size_t index) const noexcept
{
	assert(index < usedCapacity);

	return buffer[index];
}


/// \return Reference to the specified element by index position
/// \exception Accessing index which is out of range of array container, 
///               exception out_of_range is throwed
template<typename T>
inline T& array<T>::at(size_t index)
{
	if (index >= usedCapacity)
		throw std::out_of_range("There is no such element");
	return buffer[index];
}


/// 
/// \return Reference to the specified element by index position
/// \exception Accessing index which is out of range of array container, 
///               exception out_of_range is throwed
template<typename T>
inline const T& array<T>::at(size_t index) const
{
	if (index >= size)
		throw std::out_of_range("There is no such element");
	return buffer[index];
}


/// \param other - array to compare to
/// \return True if for each i this[i] == other[i] \n
/// this.capacity != other.capacity is allowed
template<typename T>
inline bool array<T>::operator==(const array& other) const noexcept( noexcept(T::operator==) )
{
	if (usedCapacity != other.usedCapacity)
		return false;
	for (size_t i = 0; i < usedCapacity; ++i) {
		if ( ! (buffer[i] == other.buffer[i]) ) // TODO may throw ?
			return false;
	}

	return true;
}




