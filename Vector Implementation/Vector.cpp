#include "Vector.h"

template<class T, class A>
Vector<T, A>::Vector()
	:_size(0), _elements(0), _space(0)
{
}

template<class T, class A>
Vector<T, A>::Vector(int s)
	:_size(s), _elements(new T[s]), _space(s)
{
	for (int index = 0; index < _size; ++index)
		_elements[index] = 0;
}
template<class T, class A>
Vector<T, A>::Vector(const Vector& arg)
	:_size(arg._size), _elements(new T[arg._size])
{
	for (int index = 0; index < arg._size; ++index)
	{
		_elements[index] = arg._elements[index];
	}
}

template<class T, class A>
Vector<T, A>::~Vector()
{
	delete[] _elements;
}

template<class T, class A>
Vector<T, A>& Vector<T, A>::operator=(const Vector& a)
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

template<class T, class A>
int Vector<T, A>::capacity() const
{
	return _space;
}

template<class T, class A>
void Vector<T, A>::push_back(const T& val)
{
	if (_space == 0)
		reserve(8);
	else if (_size == _space)
		reserve(2 * _space);

	_alloc.construct(&_elements[_size], val);

	++_size;
}

template<class T, class A>
void Vector<T, A>::reserve(int newalloc)
{
	if (newalloc <= _space) return;		// Don't decrease Vector size

	T* p = _alloc.allocate(newalloc);

	// Copy
	for(int index = 0; index < _size; ++index)
		_alloc.construct(&p[index], _elements[index]);

	// Destroy
	for(int index = 0; index < _size; ++index)
		_alloc.destroy(&_elements[index]);

	// Deallocate old space
	_alloc.deallocate(_elements, _space);

	_elements = p;
	_space = newalloc;
}

template<class T, class A>
void Vector<T, A>::resize(int newsize, T val = T())
{
	reserve(newsize);

	for (int index = _size; index < newsize; ++index)
		_alloc.construct(&_elements[i], val);

	for (int index = newsize; index < _size; ++index)
		_alloc.destroy(&_elements[index]);

	_size = newsize;
}

template<class T, class A>
int Vector<T, A>::size() const
{
	return _size;
}

template<class T, class A>
T& Vector<T, A>::at(int n)
{
	if (n < 0 || _size <= n) throw out_of_range();
	return _elements[n];
}

template<class T, class A>
const T& Vector<T, A>::at(int n) const
{
	if (n < 0 || _size <= n) throw out_of_range();
	return _elements[n];
}

template<class T, class A>
T& Vector<T, A>::operator[](int i)
{
	return _elements[i];
}

template<class T, class A>
const T & Vector<T, A>::operator[](int i) const
{
	return _elements[i];
}