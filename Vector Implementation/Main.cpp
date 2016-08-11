/*
	Author: Miguel Deniz
	Date:	8/9/2016

	Description:
	A custom implementation of C++'s STL vector.
*/

#include <iostream>
#include <string>
#include "Vector.h"

int main()
{
	Vector v(10);
	int x = v[2];
	v[3] = x;

	return 0;
}
