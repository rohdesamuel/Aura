#ifndef NFILTER__H
#define NFILTER__H

#include <vector>

#include "filter.h"
#include "sparserep.h"

using namespace std;

namespace filters
{
	class NFilter: public Filter
	{
	public:
		NFilter();
		~NFilter();

		virtual Point * add(Point * point);
		virtual Point * find(Point * point, SparseRep<double> * prob_distr, std::unordered_map<Point*, double> * distribution, double * normal_constant, distr_func dfun);

	private:
		vector<Point *> clusters;
	};
}
#endif