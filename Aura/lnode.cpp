#include "lnode.h"
#include "timer.h"

double LNode::distr_func(Point * pattern, Point * input, SparseRep<double> * input_distr)
{
	int sim = input->similarity(pattern);
	return exp((sim*sim)/10);
}

void LNode::inference()
{
	//Ready the spatial output
	sOutput.clear();
	
	//Set the probability distribution
	getInput();

	Point * pInput = filter->find(&point, NULL, &sOutput, &sOutputNormal, &(this->distr_func));

	//Create temporal output
	{
		tOutput.clear();
		
		TemporalPatterns::iterator pit;
		SpatialOutput::iterator it = sOutput.begin();
		int temp_pattern = 0;
		
		while(it != sOutput.end())
		{
			double prob = it->second * sOutputNormal;
			int set_index = tPatterns.findLower(it->first);
			TemporalOutput::iterator tempIt = tOutput.find(set_index);
			if (tempIt == tOutput.end())
			{
				if (prob > 0.0001)
					tOutput.set(set_index, prob);
			}
			else if (prob > tempIt->second)
				tOutput.set(set_index, prob);
			++it;
		}
	}

}

void LNode::getInput()
{
	point.clear();

	std::vector<int>::iterator it = mapping_indices.begin();
	int i = 0;
	while(it != mapping_indices.end())
	{
		point.set(i, input->get(*it));
		++i;
		++it;
	}
}

void LNode::learn()
{
	//Add input to node filter 
	getInput();
	Point * pInput = filter->add(&point);

	//Don't do anything if returns NULL
	if (pInput == NULL)
		return;

	//Insert into spatial pattern memory
	sPatterns.insertVertex(pInput);

	//Update markov chain
	Edge * inputEdge = NULL;
	if (prevInput != NULL)
	{
		inputEdge = sPatterns.insertEdge(prevInput, pInput);
		sPatterns.normalize(pInput);
	}
	prevInput = pInput;

#define DO_TEMPORAL_POOLING
#ifdef DO_TEMPORAL_POOLING

	//Add to temporal disjoint set template
	tPatternBuffer.add(pInput);

	//Add to Temporal Heap
	if (inputEdge != NULL)
	{
		//Add to the temporal queue
		tQueue.push(inputEdge, inputEdge);

		//Refresh the priority on the edge
		SpatialPatterns::next_iterator next_it = sPatterns.beginOut(pInput);
		while(next_it != sPatterns.endOut())
		{
			Edge * edge = *next_it;
			tQueue.refreshPriority( edge );
			++next_it;
		}
		
		//Extract Temporal Groups
		TemporalQueue tQueueBuffer;
		tPatterns = tPatternBuffer;
		
 		while(tQueue.size() > 0)
		{
			Edge * edge = tQueue.peek();
			if (edge->normal <= 0.67f)
				break;
			tQueue.pop();
			tQueueBuffer.push(edge, edge);
			if (tPatterns.size() >= 0)
				tPatterns.setunion(edge->source, edge->dest);
		}
		//Push back all the elements that were popped off the queue
		while(tQueueBuffer.size() > 0)
		{
			Edge * edge = tQueueBuffer.pop();
			tQueue.push(edge, edge);
		}
	}
#endif /* DO_TEMPORAL_POOLING */
}
