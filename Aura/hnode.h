#ifndef HNODE__H
#define HNODE__H

#include <unordered_map>

#include "node.h"
#include "sparserep.h"
#include "hashgraph.h"
#include "filter.h"
#include "dsets.h"
#include "priorityqueue.h"

class HNode : public Node
{
public:
	HNode(void):Node(){ };
	HNode(filters::Filter * filter, vector<Node*> & input):
		Node(filter), input(input){ };

	virtual void learn();
	virtual void inference();

private:

	void getInput();
	static double distr_func(Point * pattern, Point * input, SparseRep<double> * input_distr);

	/*Input Variables*/
	Point point;
	SparseRep<double> prob_distr;
	vector<Node *> input;
};
#endif /* HNode__H */