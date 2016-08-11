#pragma once

class Vector
{
public:
	explicit Vector(int s);

	Vector(const Vector& arg);

	~Vector();

	Vector& operator=(const Vector& arg);

	double& operator[](int i);
	const double& operator[](int i) const;
private:
	int _size;

	double* _elements;
};