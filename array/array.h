#pragma once

// TODO documentation to all the data members and functions


/// Ordinary array allocated in heap
template <typename T>
class array
{
private:
	T* buffer; /// array storage
	
	size_t usedCapacity; /// Number of pushed elements in array

	size_t capacity; /// Allocated memory for buffer

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
	
	
	void push_back(T);
	T& back();
	const T& back() const;

	T& operator[](size_t index); // const ?
	const T& operator[](size_t index) const;

	T& at(size_t index);
	const T& at(size_t index) const;
	
	bool operator== (const array&) const;
};

/// Copy given buffer into this.buffer \n
/// 
/// Used in operator= and copy constructor \n
template <typename T>
void array<T>::copyBuffer(T* _buffer, size_t _bufferSize) {
	for (size_t i = 0; i < _bufferSize; ++i)
		buffer[i] = _buffer[i]; /// TODO may throw
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
array<T>::array(size_t capacity) : capacity(capacity), size(0)
{
	buffer = new T[capacity]; // TODO may throw

	copy()
}


/// Just an ordinary copy consturctor
template <typename T>
array<T>::array(const array& other) {
	buffer = new T[other.capacity]; // TODO may throw

	copyBuffer(other.buffer, other.size());

	usedCapacity = other.usedCapacity;
	capacity = other.capacity;
}


/// Copy all the elems of given array into this.array \n
/// 
/// \warning std::exception is thrown if (this.capacity < other.size)
template <typename T>
array<T>& array<T>::operator=(const array& other) {
	if (this->capacity < other.size) {
		throw std::exception();
	}
	if (this != &other) {
		copy(other.buffer, other.size());
		usedCapacity = other.usedCapacity;
	}
	return *this;
}


/// Deletes allocated memory for storage(buffer)
template <typename T>
array<T>::~array() {
	deleteDynamicMemory();
}


/// Fill the container with the specified value initElem \n
/// \param initElem - the value to assign to all the elements
template <typename T>
void array<T>::fill(const T& initElem) {
	for (size_t i = 0; i < capacity; ++i)
		buffer[i] = initElem;
}


/// Checks whether array is empty
template <typename T>
inline bool array<T>::isEmpty() const {
	return usedCapacity == 0;
}


/// \return number of already pushed elements in the array
template <typename T>
inline size_t array<T>::size() const {
	return usedCapacity;
}


/// TODO
/// TODO
/// TODO
template<typename T>
inline void array<T>::push_back(T)
{
	/// TODO
}


/// TODO
/// TODO
/// TODO
template<typename T>
inline T& array<T>::back()
{
	// TODO: insert return statement here
}


/// TODO
/// TODO
/// TODO
template<typename T>
inline const T& array<T>::back() const
{
	// TODO: insert return statement here
}


/// \param index - position of the element to return
/// \return Reference to the element specified by index position
/// \warning Passing invalid argument, the behaviour is undefined
template<typename T>
inline T& array<T>::operator[](size_t index)
{
	assert(index < size);

	return buffer[index];
}


/// Working for constant instances of array
/// \param index - position of the element to return
/// \return Reference to the element specified by index position
/// \warning Passing invalid argument, the behaviour is undefined
template<typename T>
inline const T& array<T>::operator[](size_t index) const
{
	assert(index < size);

	return buffer[index];
}


/// \return Reference to the specified element by index position
/// \exception Accessing index which is out of range of array container, 
///               exception out_of_range is throwed
template<typename T>
inline T& array<T>::at(size_t index)
{
	if (index >= size)
		throw std::out_of_range();
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
		throw std::out_of_range();
	return buffer[index];
}


/// \param array to compare to
/// \return True if for each i this[i] == other[i] \n
/// this.capacity != other.capacity is allowed
template<typename T>
inline bool array<T>::operator==(const array& other) const
{
	if (usedCapacity != other.usedCapacity)
		return false;
	for (size_t i = 0; i < usedCapacity; ++i) {
		if (buffer[i] != other.buffer[i]) // TODO may throw ?
			return false;
	}

	return true;
}




