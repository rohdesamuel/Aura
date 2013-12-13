#ifndef BITSET__H
#define BITSET__H

#include <set>

class Bitset
{
public:
	Bitset();
	Bitset(Bitset && other);

	typedef std::set<unsigned int>::iterator iterator;

	void flip(unsigned int i);
	void operator()(unsigned int i, bool value);
	bool operator()(unsigned int i) const;
	bool operator==(const Bitset & other) const;
	bool operator!=(const Bitset & other) const;

	void clear();
	int count();
	int distance(const Bitset & other) const;
	int similarity(const Bitset & other) const;
	int similarity(const Bitset & other, int distance) const;
	
	iterator begin(){ return __bits.begin(); };
	iterator end(){ return __bits.end(); };

private:
	void __clear();
	void __move(Bitset && other);

	std::set<unsigned int> __bits;
};

inline bool Bitset::operator==(const Bitset & other) const{
	std::set<unsigned int>::const_iterator
		first1 = __bits.begin(),
		first2 = other.__bits.begin(),
		last1 = __bits.end(),
		last2 = other.__bits.end();
	while (first1!=last1 && first2!=last2)
	{
		if (*first1 == *first2){
			++first1; ++first2;
		}
		else
			return false;
	}
	if ((first1==last1 && first2!=last2) || (first1!=last1 && first2==last2))
		return false;
	else
		return true;
}


inline bool Bitset::operator!=(const Bitset & other) const{
	return !(*this == other);
}

inline int Bitset::distance(const Bitset & other) const
{
	std::set<unsigned int>::iterator 
		first1 = __bits.begin(),
		first2 = other.__bits.begin(),
		last1 = __bits.end(),
		last2 = other.__bits.end();
	int result = 0;
	while (first1!=last1 && first2!=last2)
	{
		if (*first1<*first2) ++first1;
		else if (*first2<*first1) ++first2;
		else { //if *first1 == *first2
			++result; ++first1; ++first2;
		}
	}
	return result;
}


inline int Bitset::similarity(const Bitset & other) const
{
	int bits = std::max<size_t>(__bits.size(), other.__bits.size());
	return distance(other) + std::min<size_t>((bits - __bits.size()),(bits - other.__bits.size()));
}


inline int Bitset::similarity(const Bitset & other, int distance) const
{
	int bits = std::max<size_t>(__bits.size(), other.__bits.size());
	return distance + std::min<size_t>((bits - __bits.size()),(bits - other.__bits.size()));
}

#endif