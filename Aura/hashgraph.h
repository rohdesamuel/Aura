#ifndef HASH_GRAPH__H
#define HASH_GRAPH__H

#include "point.h"
#include "edge.h"

#include <vector>
#include <unordered_map>


class HashGraph
{
	friend class next_itertor;

private:
	typedef unsigned long long Code_;
	typedef std::pair<Edge *, bool> EdgeInfo_;
	typedef std::unordered_map<Code_, EdgeInfo_ > EdgeData_;
	typedef std::unordered_map<Code_, Code_> Next_;
	typedef std::unordered_map<Point *, Code_> Heads_;
	typedef std::unordered_map<Point *, int> Weights_;

	Code_ ptrToCode_(Point *x, Point *y) const;
	Point *codeToDst_(Code_ code) const;
	Point *codeToSrc_(Code_ code) const;

	EdgeData_ edgeData_;

	Next_ nextIn_;
	Next_ nextOut_;
	Heads_ headsIn_;
	Heads_ headsOut_;
	Weights_ weights_;
public:
	class next_iterator {
		friend class HashGraph;
	private:
		Next_ * nextData;
		EdgeData_ * edgeData;
		Next_::iterator next_it;
	public:
		bool operator==(next_iterator & other){
			return	(edgeData == other.edgeData) &&
					(nextData == other.nextData) &&
					(next_it == other.next_it);
		}

		bool operator!=(next_iterator & other){
			return !(*this == other);
		}

		void operator++(){
			next_it = nextData->find(next_it->second);
		}

		Edge * operator*(){
			EdgeData_::iterator edge_it = edgeData->find(next_it->first);
			return (edge_it->second).first;
		}
	};

	HashGraph(){};
	~HashGraph(){};

	Edge * insertEdge(Point * x, Point * y);
	void insertVertex(Point * v);

	void normalize();
	void normalize(Point * v);

	std::vector<Edge *> getIn(Point *v) const;
	std::vector<Edge *> getOut(Point *v) const;

	next_iterator HashGraph::beginOut(Point * v);
	next_iterator HashGraph::beginIn(Point * v);
	next_iterator HashGraph::endOut();
	next_iterator HashGraph::endIn();
};
#endif /* HASH_GRAPH__H */