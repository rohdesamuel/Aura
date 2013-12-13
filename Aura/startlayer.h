#ifndef STARTLAYER__H
#define STARTLAYER__H

#include "layer.h"
#include "lnode.h"

template <typename FilterTy>
class StartLayer : public Layer
{
public:
	StartLayer():Layer(){};
	StartLayer(FilterTy * filter, int num_nodes, int rfield){
		nodes.reserve(num_nodes);
		for (int i = 0; i < num_nodes; ++i)
		{
			std::vector<int> mapping_indices(rfield);
			for (int j = 0; j < rfield; j ++)
				mapping_indices[j] = i * rfield + j;
			nodes.push_back( new LNode( new FilterTy (*filter), &input, mapping_indices ) );
		}
	};

	void learn();
	void inference();

	Point input;
};

template <typename FilterTy>
void StartLayer<FilterTy>::learn()
{
	int num_nodes = nodes.size();
	for (int i = 0; i < num_nodes; ++i)
		nodes[i]->learn();
}


template <typename FilterTy>
void StartLayer<FilterTy>::inference()
{
	int num_nodes = nodes.size();
	for (int i = 0; i < num_nodes; ++i)
		nodes[i]->inference();
}

#endif
