#pragma once

#include <memory>

struct out_of_range
{

};

template<class T, class A = std::allocator<T>> class Vector
{
public:
	/// Constructors
	// Default Constructor
	Vector();

	explicit Vector(int s);

	// Copy Constructor
	Vector(const Vector& arg);

	// Copy Assingment
	Vector& operator=(const Vector& arg);

	// Destructor
	~Vector();

	int capacity() const;

	void push_back(const T& d);

	void reserve(int newalloc);

	// Make the Vector have newsize elements
	// Initialize each new element with the default value 0.0
	void resize(int newsize, T val = T());

	int size() const;

	T& at(int n);
	const T& at(int n) const;

	// Subscript Overload
	T& operator[](int i);
	const T& operator[](int i) const;
private:
	int	_size;		// Number of elements in Vector
	T*	_elements;	// Pointer to first element of Vector
	int	_space;		// Total space used by Vector including
					// elements and free space.
	A	_alloc;
};