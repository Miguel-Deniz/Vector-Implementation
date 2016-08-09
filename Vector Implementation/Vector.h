#pragma once

class Vector
{
public:
	Vector(int s);
	~Vector();
private:
	int _size;
	double* _elements;
};