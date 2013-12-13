#pragma once
#ifndef FILTER__H
#define FILTER__H

#include <unordered_map>
#include <vector>
#include "point.h"
#include "sparserep.h"

namespace filters
{
	class Filter
	{
	protected:
		typedef double (*distr_func)(Point *, Point *, SparseRep<double> *);
	public:
		virtual Point * add(Point * point) = 0;
		virtual Point * find(Point * point, SparseRep<double> * prob_distr, std::unordered_map<Point*, double> * distribution, double * normal_constant, distr_func dfun) = 0;
	};
}
#endif