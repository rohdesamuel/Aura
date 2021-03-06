#ifndef SPARSEREP__H
#define	SPARSEREP__H

#include <map>

template<typename _Ty>
class SparseRep
{
public:
	SparseRep();
	SparseRep(SparseRep<_Ty> && other);

	typedef typename std::map<size_t, _Ty>::iterator iterator;
	typedef typename std::map<size_t, _Ty>::const_iterator const_iterator;

	void set(size_t i, _Ty t);
	_Ty & get(size_t i);

	void erase(size_t i);
	void erase(iterator it);
	void clear();
	int count() const;

	iterator begin() { return __nums.begin(); };
	iterator end()  { return __nums.end(); };
	iterator find(size_t i) { return __nums.find(i); };

	const_iterator begin() const { return __nums.begin(); };
	const_iterator end() const { return __nums.end(); };
	const_iterator find(size_t i) const { return __nums.find(i); };

private:
	void __clear();
	void __move(SparseRep<_Ty> && other);

	std::map<size_t, _Ty> __nums;
};

template<typename _Ty>
SparseRep< _Ty>::SparseRep(){ };

template<typename _Ty>
SparseRep< _Ty>::SparseRep(SparseRep< _Ty> && other)
{ 
	__move(std::move(other));
}

template<typename _Ty>
void SparseRep< _Ty>::__move(SparseRep< _Ty> && other)
{ 
	__nums = std::move(other.__nums);
}

template<typename _Ty>
void SparseRep< _Ty>::clear()
{ 
	__nums.clear();
}


template<typename _Ty>
void SparseRep< _Ty>::set(size_t i, _Ty t)
{
	iterator it = __nums.find(i);
	if (it == __nums.end())
		__nums.insert( std::pair<size_t, _Ty>(i, t));
	else
		it->second = t;
}

template<typename _Ty>
_Ty & SparseRep< _Ty>::get(size_t i)
{
	iterator it = __nums.find(i);
	return it->second;
}

template<typename _Ty>
int SparseRep< _Ty>::count() const
{
	return __nums.size();
}

template<typename _Ty>
void SparseRep< _Ty>::erase(size_t i)
{
	erase(__nums.find(i));
}

template<typename _Ty>
void SparseRep< _Ty>::erase(iterator it)
{
	__nums.erase(it);
}

#endif