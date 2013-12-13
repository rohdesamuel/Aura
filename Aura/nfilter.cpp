#include "nfilter.h"
namespace filters
{
	NFilter::NFilter():Filter() { }

	NFilter::~NFilter() { }

	Point * NFilter::find(Point * point, SparseRep<double> * prob_distr, std::unordered_map<Point*, double> * distribution, double * normal_constant, distr_func dfun)
	{
		Point * ret = NULL;
		
		*normal_constant = 0;

		int best = -1;
		double bestSim = 0;
		for (unsigned int i = 0; i < clusters.size(); ++i)
		{
			double sim = dfun(clusters[i], NULL, prob_distr);
			distribution->insert(std::make_pair(clusters[i], sim));
			*normal_constant += sim;

			if (sim >= bestSim)
			{
				bestSim = sim;
				best = i;
			}
		}
		*normal_constant = 1 / *normal_constant;

		if (best != -1)
			ret = clusters[best];
		return ret;
	}

	
	Point * NFilter::add(Point * point)
	{
		Point * ret = NULL;
		bool found = false;
		for (unsigned int i = 0; i < clusters.size(); ++i)
		{
			if (*clusters[i] == *point)
			{
				found = true;
				ret = clusters[i];
				break;
			}
		}
		
		if (!found)
			clusters.push_back(ret = new Point(*point));

		return ret;
	}
}