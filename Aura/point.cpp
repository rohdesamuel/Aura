#include "point.h"

void Point::set(int i, bool value)
{
	__data(i, value);
}

bool Point::get(int i)
{
	return __data(i);
}

void Point::flip(int i)
{
	__data.flip(i);
}

void Point::clear()
{
	__data.clear();
}

