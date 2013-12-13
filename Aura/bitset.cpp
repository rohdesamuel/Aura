#include <math.h>
#include "bitset.h"


Bitset::Bitset(){ };

void Bitset::clear()
{ 
	__bits.clear();
};

void Bitset::flip(unsigned int i)
{
	iterator it = __bits.find(i);
	if (it == __bits.end())
		__bits.insert(i);
	else
		__bits.erase(it);
}


void Bitset::operator()(unsigned int i, bool value)
{
	if (value)
		__bits.insert(i);
	else
		__bits.erase(i);
};


bool Bitset::operator()(unsigned int i) const
{
	if (__bits.find(i) != __bits.end())
			return true;
	return false;
}

int Bitset::count()
{
	return __bits.size();
}

