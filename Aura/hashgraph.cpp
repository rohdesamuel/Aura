#include "hashgraph.h"

HashGraph::next_iterator HashGraph::beginOut(Point * v){
	next_iterator nxt;
	Heads_::iterator heads_it = headsOut_.find(v);
	nxt.nextData = &nextOut_;
	nxt.edgeData = &edgeData_;
	if (heads_it != headsOut_.end())
		nxt.next_it = nextOut_.find( heads_it->second );
	else
		nxt.next_it = nextOut_.end();
	return nxt;
}

HashGraph::next_iterator HashGraph::beginIn(Point * v){
	next_iterator nxt;
	Heads_::iterator heads_it = headsIn_.find(v);
	nxt.nextData = &nextIn_;
	nxt.edgeData = &edgeData_;
	if (heads_it != headsIn_.end())
		nxt.next_it = nextIn_.find( heads_it->second );
	else
		nxt.next_it = nextIn_.end();
	return nxt;
}

HashGraph::next_iterator HashGraph::endOut(){
	next_iterator nxt;
	nxt.nextData = &nextOut_;
	nxt.edgeData = &edgeData_;
	nxt.next_it = nextOut_.end();
	return nxt;
}

HashGraph::next_iterator HashGraph::endIn(){
	next_iterator nxt;
	nxt.nextData = &nextIn_;
	nxt.edgeData = &edgeData_;
	nxt.next_it = nextIn_.end();
	return nxt;
}

Point * HashGraph::codeToDst_(Code_ code) const
{
	return  (Point *) code;
}

Point *HashGraph::codeToSrc_(Code_ code) const
{
	return (Point *) (code >> (sizeof(long) * 8));
}

HashGraph::Code_ HashGraph::ptrToCode_(Point *src, Point *dst) const
{
	return (Code_(src) << (sizeof(long) * 8)) | Code_(dst);
}

void HashGraph::insertVertex(Point *v)
{
	if (weights_.find(v) == weights_.end())
	{
		headsIn_[v] = 0;
		headsOut_[v] = 0;
		weights_[v] = 0;
	}
}

Edge * HashGraph::insertEdge(Point *src, Point *dst)
{
	Edge * ret;
	
	Code_ src_code = ptrToCode_(src, dst);
	Code_ dst_code = ptrToCode_(dst, src);

	++weights_[dst];

	EdgeData_::iterator edge_it;
	if ((edge_it = edgeData_.find(src_code)) == edgeData_.end())
	{
		ret = new Edge(src, dst);
		edgeData_[src_code] = EdgeInfo_(ret, true);
	}
	else
	{
		ret = (edge_it->second).first;
		if ((edge_it->second).second == false)
			(edge_it->second).second = true;
		else
		{
			++ret->weight;
			return ret;
		}
	}
	
	if (edgeData_.find(dst_code) == edgeData_.end())
		edgeData_[dst_code] = EdgeInfo_(new Edge(dst, src), false);

	nextOut_[src_code] = headsOut_[src];
	headsOut_[src] = src_code;

	nextIn_[src_code] = headsIn_[dst];
	headsIn_[dst] = src_code;

	return ret;
}

void HashGraph::normalize()
{
	Weights_::iterator weight_it = weights_.begin();
	while( weight_it != weights_.end())
	{
		Point * point = weight_it->first;
		float weight = (float)weight_it->second;

		Code_ head = headsOut_[point];
		std::unordered_map<Code_, Code_>::iterator head_it = nextIn_.find(head);
		while( (head_it = nextOut_.find(head)) != nextOut_.end() )
		{
			EdgeData_::iterator edge_it = edgeData_.find(head);
			((edge_it->second).first)->normal = (float)((edge_it->second).first)->weight / weight;
			head = head_it->second;
		}
		++weight_it;
	}
}

void HashGraph::normalize(Point * v)
{
	Weights_::iterator weight_it = weights_.find(v);
	if (weight_it == weights_.end())
		return;

	float weight = (float)weight_it->second;
	Code_ head = headsOut_[v];
	std::unordered_map<Code_, Code_>::iterator head_it = nextIn_.find(head);
	while( (head_it = nextOut_.find(head)) != nextOut_.end() )
	{
		EdgeData_::iterator edge_it = edgeData_.find(head);
		((edge_it->second).first)->normal = (float)((edge_it->second).first)->weight / weight;
		head = head_it->second;
	}
}

std::vector<Edge* > HashGraph::getIn(Point *v) const
{
	std::vector<Edge *> ret;
	std::unordered_map<Point *, Code_>::const_iterator it = headsIn_.find(v);
	if (it == headsIn_.end())
		return ret;

	Code_ head = it->second;
	std::unordered_map<Code_, Code_>::const_iterator head_it = nextIn_.find(head);
	while( (head_it = nextIn_.find(head)) != nextIn_.end() )
	{
		EdgeData_::const_iterator edge_it = edgeData_.find(head);
		ret.push_back((edge_it->second).first);
		head = head_it->second;
	}
	
	return ret;
}

std::vector<Edge* > HashGraph::getOut(Point *v) const
{
	std::vector<Edge *> ret;
	std::unordered_map<Point *, Code_>::const_iterator it = headsOut_.find(v);
	if (it == headsOut_.end())
		return ret;

	Code_ head = it->second;
	std::unordered_map<Code_, Code_>::const_iterator head_it = nextIn_.find(head);
	while( (head_it = nextOut_.find(head)) != nextOut_.end() )
	{
		EdgeData_::const_iterator edge_it = edgeData_.find(head);
		ret.push_back((edge_it->second).first);
		head = head_it->second;
	}
	
	return ret;
}

