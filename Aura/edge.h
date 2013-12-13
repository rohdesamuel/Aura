#ifndef EDGE__H
#define EDGE__H

class Point;

class Edge
{
public:
	Edge(): source(NULL), dest(NULL), weight(1), normal(0) { };
	Edge(Point * Source, Point * Dest): source(Source), dest(Dest), weight(1), normal(0){ };
	
	int weight;
	float normal;
	Point * source;
	Point * dest;

	struct __weight_compare {
		bool operator()( Edge * e1, Edge * e2 ){ return(e1->weight > e2->weight); };
	};

	struct __normal_compare {
		bool operator()( Edge * e1, Edge * e2 ){ return(e1->normal > e2->normal); };
	};
};

#endif