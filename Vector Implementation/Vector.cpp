#include "Vector.h"

Vector::Vector(int s)
	:_size(s), _elements(new double[s])
{
}

Vector::Vector(const Vector& arg)
	:_size(arg._size), _elements(new double[arg._size])
{
	for (int index = 0; index < arg._size; ++index)
	{
		_elements[index] = arg._elements[index];
	}
}

Vector::~Vector()
{
	delete[] _elements;
}

Vector& Vector::operator=(const Vector& arg)
{
	double* p = new double[arg._size];

	for (int index = 0; index < arg._size; ++index)
		p[index] = arg._elements[index];

	delete[] _elements;

	_size = arg._size;

	return *this;
}

double& Vector::operator[](int i)
{
	return _elements[i];
}

const double& Vector::operator[](int i) const
{
	return _elements[i];
}
