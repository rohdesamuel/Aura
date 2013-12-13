#ifndef DSETS__H
#define DSETS__H

#include <map>
#include <vector>

template<class T>
class DSets 
{
private:
	void __unionbysize ( int root1, int root2 );
	int __find ( int elem );
    
	std::map<T, int > __elementDictionary;
	std::vector<int> __data;
	std::vector<int> __set_indices;
	int __size;

public:
	typedef typename std::map<T, int >::iterator iterator;
	typedef typename std::map<T, int >::const_iterator const_iterator;

	DSets():__size(0) { };
	void add (T elem);
	int find (T elem);
	int findLower (T elem);

	void setunion( T a, T b);
	void setunion( int a, int b);
	int size() { return __size; };

	iterator begin(){return __data.begin();};
	const_iterator begin() const{return __elementDictionary.begin();};
	iterator end(){return __data.end();};
	const_iterator end() const {return __elementDictionary.end();};
};

template<class T>
void DSets<T>::add( T elem )
{
	if (__elementDictionary.find( elem ) == __elementDictionary.end())
	{
		int new_index = __data.size();
		pair<T, int> element(elem, new_index);
		__elementDictionary.insert(element);
		__data.push_back(-1);
		__set_indices.push_back(new_index);
		++__size;
	}
}

template<class T>
int DSets<T>::find ( T elem )
{ 
	map< T, int>::iterator it = __elementDictionary.find(elem);
	if (it != __elementDictionary.end())
		return __find((*it).second);
	return -1;
}

template<class T>
int DSets<T>::findLower ( T elem )
{ 
	map< T, int>::iterator it = __elementDictionary.find(elem);
	if (it != __elementDictionary.end())
		return __set_indices[__find((*it).second)];
	return -1;
}


template<class T>
int DSets<T>::__find ( int elem )
{ 
	if ((unsigned int)elem < __data.size() )
	{
		if ( __data[elem] < 0 ) 
			return elem;
		else
			return __data[elem] = __find ( __data[elem] );
	}
	return -1;
}

template<class T>
void DSets<T>::setunion( T a, T b)
{
	int seta = find(a), 
		setb = find(b);
	if (seta >= 0 && setb >= 0)
		__unionbysize( seta, setb );
}

template<class T>
void DSets<T>::setunion( int a, int b)
{
	int seta = find(a), 
		setb = find(b);
	if (seta >= 0 && setb >= 0)
		__unionbysize( seta, setb );
}

template<class T>
void DSets<T>::__unionbysize ( int root1, int root2 )
{
    int new_size = __data[root1] + __data[root2];
    if ( root1 > root2 ) 
    {
        __data[root2] = root1;
        __data[root1] = new_size;
		--__size;
    }
    else if (root1 < root2)
    {
        __data[root1] = root2;
        __data[root2] = new_size;
		--__size;
    }

	if (__set_indices[root2] > __set_indices[root1])
		__set_indices[root2] = __set_indices[root1];
	else
		__set_indices[root1] = __set_indices[root2];
		

}


#endif
