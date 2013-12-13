#ifndef POINT__H
#define POINT__H

#include "bitset.h"

using namespace std;

class Point
{
public:
	Point() { };
	Point(Bitset && Data):__data(Data) { };

	typedef Bitset::iterator iterator;

	int size(){return __data.count(); };

	int distance(const Point & point) const;
	int distance(const Point * point) const;

	int similarity(const Point & point) const;
	int similarity(const Point * point) const;
	int similarity(const Point & point, int distance) const;
	int similarity(const Point * point, int distance) const;

	bool operator==(const Point & point) const;
	bool operator!=(const Point & point) const;

	bool get(int i);
	void set(int i, bool value);
	void flip(int i);
	void clear();

	iterator begin(){ return __data.begin(); };
	iterator end(){ return __data.end(); };

private:
	Bitset __data;
};

inline int Point::distance(const Point & point) const
{
	return __data.distance(point.__data);
}

inline int Point::distance(const Point * point) const
{
	return __data.distance(point->__data);
}

inline int Point::similarity(const Point & point) const
{
	return __data.similarity(point.__data);
}

inline int Point::similarity(const Point * point) const
{
	return __data.similarity(point->__data);
}

inline int Point::similarity(const Point & point, int distance) const
{
	return __data.similarity(point.__data, distance);
}

inline int Point::similarity(const Point * point, int distance) const
{
	return __data.similarity(point->__data, distance);
}

inline bool Point::operator==(const Point & point) const
{
	return this->__data == point.__data;
}

inline bool Point::operator!=(const Point & point) const
{
	return !(this->__data == point.__data);
}

#endif