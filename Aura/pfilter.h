#ifndef PFILTER__H
#define PFILTER__H

#include <vector>
#include <algorithm>
#include <utility>

#include "filter.h"
#include "sparserep.h"

using namespace std;

#define MIN_AVG 0.75f

namespace filters
{	
	class PFilter: public Filter
	{
	public:
		PFilter(int Radius, int Active):radius(Radius),active(Active),iterations(0) { 
			__precision = 10000;
		}
		~PFilter();

		virtual Point * add(Point * point);
		virtual Point * find(Point * point, SparseRep<double> * prob_distr, std::unordered_map<Point*, double> * distribution, double * normal_constant, distr_func dfun);

		int iterations;
		int radius;
		int active;

	private:
		struct __compare {
			inline bool operator()( pair<int, int> & p1, pair<int, int> & p2 ){ return(p1.second < p2.second); };
		};

		int __precision;
		SparseRep<int> distr;
		vector<int> count;
		vector<SparseRep<int> > means;
		vector<Point *> clusters;
	};
}
#endif