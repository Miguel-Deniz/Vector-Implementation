#pragma once

struct out_of_range
{

};

template<class T> class Vector
{
public:
	/* ----- Constructors ----- */

	// Default constructor
	Vector();

	explicit Vector(int s);

	// Copy constructor
	Vector(const Vector& arg);

	// Copy Assingment
	Vector<T>& operator=(const Vector<T>& arg);

	// Destructor
	~Vector();

	/*----------------------------*/





	/* -------- ITERATORS --------*/

	class iterator;

	iterator begin();

	const iterator begin() const;

	iterator end();
	
	const iterator end() const;

	const iterator cbegin() const;

	const iterator cend() const;

	/*----------------------------*/





	/* -------- CAPACITY -------- */

	bool empty() const;

	// Returns size of allocated storate capacity
	size_t capacity() const;

	// Requests a change in capacity
	// reserve() will never decrase the capacity.
	void reserve(int newmalloc);

	// Changes the Vector's size.
	// If the newsize is smaller, the last elements will be lost.
	// Has a default value param for custom values when resizing.
	void resize(int newsize, T val = T());

	// Returns the size of the Vector (number of elements). 
	size_t size() const;

	// Returns the maximum number of elements the Vector can hold
	size_t max_size() const;

	// Reduces capcity to fit the size
	void shrink_to_fit();

	/*----------------------------*/





	/* -------- MODIFIERS --------*/

	// Removes all elements from the Vector
	// Capacity is not changed.
	void clear();

	// Inserts element at the back
	void push_back(const T& d);

	// Removes the last element from the Vector
	void pop_back();

	/*----------------------------*/





	/* ----- ELEMENT ACCESS ----- */

	// Access elements with bounds checking
	T& at(int n);

	// Access elements with bounds checking for constant Vectors.
	const T& at(int n) const;

	// Access elements, no bounds checking
	T& operator[](int i);

	// Access elements, no bounds checking
	const T& operator[](int i) const;

	// Returns a reference to the first element
	T& front();

	// Returns a reference to the first element
	const T& front() const;

	// Returns a reference to the last element
	T& back();

	// Returns a reference to the last element
	const T& back() const;

	// Returns a pointer to the array used by Vector
	T* data();

	// Returns a pointer to the array used by Vector
	const T* data() const;

	/*----------------------------*/

private:
	size_t	_size;		// Number of elements in Vector
	T*		_elements;	// Pointer to first element of Vector
	size_t	_space;		// Total space used by Vector including
						// elements and free space.
};



template<class T> class Vector<T>::iterator
{
public:
	iterator(T* p)
		:_curr(p)
	{}

	iterator& operator++()
	{
		_curr++;
		return *this;
	}

	iterator& operator--()
	{
		_curr--;
		return *this;
	}

	T& operator*()
	{
		return *_curr;
	}

	bool operator==(const iterator& b) const
	{
		return *_curr == *b._curr;
	}

	bool operator!=(const iterator& b) const
	{
		return *_curr != *b._curr;
	}

private:
	T* _curr;
};



// Constructors/Destructor
template<class T>
Vector<T>::Vector()
	:_size(0), _elements(0), _space(0)
{}

template<class T>
inline Vector<T>::Vector(int s)
	:_size(s), _elements(new T[s], _space(s))
{
	for (int index = 0; index < _size; ++index)
		_elements[index] = T();
}

template<class T>
inline Vector<T>::Vector(const Vector & arg)
	:_size(arg._size), _elements(new T[arg._size])
{
	for (int index = 0; index < arg._size; ++index)
		_elements[index] = arg._elements[index];
}

template<class T>
inline Vector<T>& Vector<T>::operator=(const Vector<T>& a)
{
	if (this == &a) return *this;	// Self-assingment not work needed

									// Current Vector has enough space, so there is no need for new allocation
	if (a._size <= _space)
	{
		for (int index = 0; index < a._size; ++index)
		{
			_elements[index] = a._elements[index];
			_size = a._size;
			return *this;
		}
	}

	T* p = new T[a._size];

	for (int index = 0; index < a._size; ++index)
		p[index] = a._elements[index];

	delete[] _elements;
	_size = a._size;
	_space = a._size;
	_elements = p;
	return *this;
}

template<class T>
Vector<T>::~Vector()
{
	delete[] _elements;
}



// Iterators
template<class T>
inline typename Vector<T>::iterator Vector<T>::begin()
{	
	return Vector<T>::iterator(&_elements[0]);
}

template<class T>
inline typename const Vector<T>::iterator Vector<T>::begin() const
{
	return Vector<T>::iterator(&_elements[0]);
}

template<class T>
inline typename Vector<T>::iterator Vector<T>::end()
{
	return Vector<T>::iterator(&_elements[_size]);
}

template<class T>
inline typename const Vector<T>::iterator Vector<T>::end() const
{
	return Vector<T>::iterator(&_elements[_size]);
}

template<class T>
inline typename const Vector<T>::iterator Vector<T>::cbegin() const
{
	return Vector<T>::iterator(&_elements[0]);
}

template<class T>
inline typename const Vector<T>::iterator Vector<T>::cend() const
{
	return Vector<T>::iterator(&_elements[_size]);
}



// Capacity
template<class T>
inline bool Vector<T>::empty() const
{
	return (_size == 0);
}

template<class T>
inline size_t Vector<T>::capacity() const
{
	return _space;
}

template<class T>
inline void Vector<T>::reserve(int newalloc)
{
	if (newalloc <= _space) return;

	T* p = new T[newalloc];

	for (int i = 0; i < _size; ++i)
		p[i] = _elements[i];

	delete[] _elements;

	_elements = p;

	_space = newalloc;
}

template<class T>
inline void Vector<T>::resize(int newsize, T val)
{
	reserve(newsize);

	for (int index = _size; index < newsize; ++index)
		_elements[i] = T();

	_size = newsize;
}

template<class T>
inline size_t Vector<T>::size() const
{
	return _size;
}



// Modifiers
template<class T>
inline void Vector<T>::push_back(const T& d)
{
	if (_space == 0)
		reserve(8);
	else if (_size == _space)
		reserve(2 * _space);

	_elements[_size] = d;

	++_size;
}



// Accessors
template<class T>
inline T & Vector<T>::at(int n)
{
	if (n < 0 || _size <= n) throw out_of_range();
	return _elements[n];
}

template<class T>
inline const T & Vector<T>::at(int n) const
{
	if (n < 0 || _size <= n) throw out_of_range();
	return _elements[n];
}

template<class T>
inline T & Vector<T>::operator[](int i)
{
	return _elements[i];
}

template<class T>
inline const T & Vector<T>::operator[](int i) const
{
	return _elements[i];
}

template<class T>
inline T& Vector<T>::front()
{
	return _elements[0];
}

template<class T>
inline const T& Vector<T>::front() const
{
	return _elements[0];
}

template<class T>
inline T& Vector<T>::back()
{
	return _elements[_size - 1];
}

template<class T>
inline const T& Vector<T>::back() const
{
	return _elements[_size - 1];
}

template<class T>
inline T* Vector<T>::data()
{
	return _elements;
}

template<class T>
inline const T* Vector<T>::data() const
{
	return _elements;
}

