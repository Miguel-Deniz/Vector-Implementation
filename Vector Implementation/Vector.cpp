#include "Vector.h"

Vector::Vector(int s)
	:_size(s), _elements(new double[s])
{
}

Vector::~Vector()
{
	delete[] _elements;
}
