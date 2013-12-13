#ifndef LINLAYER__H
#define LINLAYER__H

#include "layer.h"
#include "hnode.h"

template <typename FilterTy>
class LinkLayer : public Layer
{
public:
	LinkLayer():Layer(){};
	LinkLayer(FilterTy * filter, Layer * layer, int num_nodes, int rfield){
		nodes.reserve(num_nodes);
		for (int i = 0; i < num_nodes; ++i)
		{
			std::vector<Node*> input(rfield);
			for (int j = 0; j < rfield; j ++)
				input[j] = layer->nodes[i * rfield + j];
			nodes.push_back( new HNode( new FilterTy (*filter), input) );
		}
	};

	void learn();
	void inference();
};

template <typename FilterTy>
void LinkLayer<FilterTy>::learn()
{
	int num_nodes = nodes.size();
	for (int i = 0; i < num_nodes; ++i)
		nodes[i]->learn();
}


template <typename FilterTy>
void LinkLayer<FilterTy>::inference()
{
	int num_nodes = nodes.size();
	for (int i = 0; i < num_nodes; ++i)
		nodes[i]->inference();
}

#endif