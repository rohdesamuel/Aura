#ifndef LNODE__H
#define LNODE__H

#include <unordered_map>

#include "node.h"
#include "sparserep.h"
#include "hashgraph.h"
#include "filter.h"
#include "dsets.h"
#include "priorityqueue.h"

class LNode : public Node
{
public:
	LNode(void):Node(){ };
	LNode(filters::Filter * filter, Point * input, vector<int> & mapping_indices):
		Node(filter), input(input), mapping_indices(mapping_indices){ };

	virtual void learn();
	virtual void inference();

private:
	void getInput();
	static double distr_func(Point * pattern, Point * input, SparseRep<double> * input_distr);

	/*Input Variables*/
	Point* input;
	Point point;
	vector<int> mapping_indices;
};
#endif /* LNode__H */