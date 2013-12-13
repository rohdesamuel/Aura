#ifndef LAYER__H
#define LAYER__H

#include "point.h"
#include "node.h"

class Layer 
{ 
public:
	virtual void learn() = 0;
	virtual void inference() = 0;
	vector<Node*> nodes;
};

//class Layer : public SuperLayer { };

#endif