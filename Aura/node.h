#ifndef NODE__H
#define NODE__H

#include <unordered_map>

#include "sparserep.h"
#include "hashgraph.h"
#include "filter.h"
#include "dsets.h"
#include "priorityqueue.h"

class SuperNode
{
public:
	SuperNode(void):prevInput(NULL), sOutputNormal(0), tOutputNormal(0){ };
	SuperNode(filters::Filter * filter):filter(filter), prevInput(NULL), sOutputNormal(0), tOutputNormal(0){ };

	virtual void learn() = 0;
	virtual void inference() = 0;

	typedef std::unordered_map<Point *, double> SpatialOutput;
	typedef SparseRep<double> TemporalOutput;
	typedef HashGraph SpatialPatterns;
	typedef DSets<Point* > TemporalPatterns;
	typedef PriorityQueue<Edge*, Edge*, typename Edge::__normal_compare> TemporalQueue;

	//Spatial Patterns
	SpatialPatterns sPatterns;

	//Temporal Patterns
	TemporalPatterns tPatterns;
	TemporalPatterns tPatternBuffer;
	
	//Priority Queue for sorting temporal patterns
	TemporalQueue tQueue;
	
	/*Output Variables*/
	//Temporal
	TemporalOutput tOutput;
	double tOutputNormal;

	//Spatial
	SpatialOutput sOutput;
	double sOutputNormal;

	//State Variables
	Point * prevInput;

	//Point filter
	filters::Filter * filter; 
};

class Node : public SuperNode
{
public:
	Node():SuperNode() { };
	Node(filters::Filter * filter):SuperNode(filter) { };
};

#endif /* NODE__H */