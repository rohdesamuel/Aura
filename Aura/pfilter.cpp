#include "pfilter.h"

namespace filters
{
	PFilter::~PFilter()
	{

	}

	
	Point * PFilter::find(Point * point, SparseRep<double> * prob_distr, std::unordered_map<Point*, double> * distribution, double * normal_constant, distr_func dfun)
	{
		Point * ret = NULL;
		
		*normal_constant = 0;

		//Iterate to find first match with distance >= radius
		//This search should be replaced with a (kdtree?) for faster nearest neghbor querying
		int best = -1;
		double bestDis = 0;
		for (unsigned int i = 0; i < clusters.size(); ++i)
		{
			int dis = point->distance(clusters[i]);
			double sim = dfun(clusters[i], point, NULL);
			distribution->insert(std::make_pair(clusters[i], sim));
			*normal_constant += sim;

			if ( (dis >= radius || (point->size() == 0 && clusters[i]->size() == 0)) && dis >= bestDis)
			{
				bestDis = dis;
				best = i;
			}
		}
		*normal_constant = 1 / *normal_constant;

		if (best != -1)
			ret = clusters[best];
		return ret;
	}

	
	Point * PFilter::add(Point * point)
	{
		Point * ret = NULL;
	
		//Iterate to find first match with distance >= radius
		//This search should be replaced with a (kdtree?) for faster nearest neghbor querying
		int best = -1;
		int bestDis = 0;
		for (unsigned int i = 0; i < clusters.size(); ++i)
		{
			int dis = point->distance(clusters[i]);
			if ( (dis >= radius || (point->size() == 0 && clusters[i]->size() == 0)) && dis >= bestDis)
			{
				bestDis = dis;
				best = i;
			}
		}

		if (best != -1)
		{
			vector<pair<int,int> > heap;
			++count[best];
			//Recompute the means with the new data point
			SparseRep<int>::iterator it = means[best].begin();
			
			while(it != means[best].end())
			{
				means[best].set(it->first, (it->second + (point->get(it->first) * __precision)) / 2);
				if (distr.find(it->first) == distr.end())
					distr.set(it->first, 0);
				distr.set(it->first, (distr.get(it->first) + point->get(it->first)) / 2);
				heap.push_back(pair<int,int>(it->first, it->second)); std::push_heap(heap.begin(), heap.end(), PFilter::__compare());
				++it;
			}

			//This Recomputes the new code for a data point to match to
			(clusters[best])->clear();
			for (int j = 0; j < active && heap.size() > 0; ++j)
			{
				int index = heap.front().first;
				(clusters[best])->set(index , true);
				std::pop_heap(heap.begin(), heap.end(), PFilter::__compare()); heap.pop_back();
			}

			//Only return a cluster when it's trained 
			//if (count[best] > 5)
			ret = clusters[best];
		}
		else if (point->size() == 0 || point->size() >= radius)
		{
			count.push_back(0);
			means.push_back(SparseRep<int>());
			
			Point::iterator it = point->begin();
			while(it != point->end())
			{
				(means.back()).set(*it, point->get(*it) * __precision);
				++it;
			}
			clusters.push_back(new Point(*point));
			ret = clusters.back();
		}

		++iterations;
		return ret;
	}
}