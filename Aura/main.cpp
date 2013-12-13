#include <windows.h>
#include <time.h>
#include <iostream>
#include <vector>

using namespace std;

#include "nfilter.h"
#include "pfilter.h"
#include "startlayer.h"
#include "linklayer.h"
#include "dsets.h"
#include "cmwc.h"
#include "bitset.h"
#include "timer.h"

int main()
{
	const int dim = 1024;
	const int rfield = 16;
	const int active = 8;
	const int radius = 2;

	const int width = 1;
	const int height = 16;
	const int dis = 16;
	const int input_data_size = 4;
	const int num_temp_patterns = 2;

	Point inputData[num_temp_patterns][input_data_size];
	for (int i = 0; i < input_data_size; ++i)
	{
		int space = 8;
		for (int j = 0; j < active; ++j)
		{
			inputData[0][i].set((i*space) + j, true);
		}
	}

	for (int i = 0; i < input_data_size; ++i)
	{
		int space = 16;
		for (int j = 0; j < active*2; ++j)
		{
			inputData[1][i].set((i*space) + j, true);
		}
	}


	filters::PFilter pfilter(radius, active);
	filters::NFilter nfilter;
	
	StartLayer<filters::PFilter> layer_low(&pfilter, dim/rfield, rfield);
	LinkLayer<filters::NFilter> layer_high(&nfilter, &layer_low, dim/rfield/4, 4);

	LARGE_INTEGER start, end, freq;
	QueryPerformanceFrequency(&freq);
	double avg = 0;
	int count = 0;
	cmwc::srand(0);//time(NULL));
	for (int j = 0; j < 1; ++j)
	{
		for (int i = 0; i < 1000; ++i)
		{
			Bitset noise;
			int noise_count = 0;//cmwc::rand() % 128;
			while(noise.count() < noise_count)
			{
				noise(cmwc::rand()%dim, true);
			}
			Bitset::iterator it = noise.begin();
			layer_low.input = inputData[j][i%input_data_size];
			while(it != noise.end())
			{
				layer_low.input.flip(*it);
				++it;
			}
			
			QueryPerformanceCounter(&start);
			layer_low.learn();
			//layer_low.inference();
			//layer_high.learn();
			//layer_high.inference();
			QueryPerformanceCounter(&end);
			avg += end.QuadPart - start.QuadPart;
			++count;
			if (i % 10 == 0)
				cout<<i<<endl;
		}
	}
	Timer timer("test");
	timer.average_time();
	timer.average_cycles();
	for (int j = 0; j < 1; ++j)
	{
		for (int i = 0; i < 0; ++i)
		{
			Bitset noise;
			int noise_count = 0;//cmwc::rand() % 128;
			while(noise.count() < noise_count)
			{
				noise(cmwc::rand()%dim, true);
			}
			Bitset::iterator it = noise.begin();
			layer_low.input = inputData[j][i%input_data_size];
			while(it != noise.end())
			{
				layer_low.input.flip(*it);
				++it;
			}
			QueryPerformanceCounter(&start);
			layer_low.inference();
			layer_high.learn();
			layer_high.inference();
			QueryPerformanceCounter(&end);
			
			
			avg += end.QuadPart - start.QuadPart;
			++count;

			if (i % 10 == 0)
				cout<<i<<endl;
		}
	}

	cout << "Avg. Clock Cycles : " << (avg/count) <<endl;
	cout << "Avg. Layer Time   : " << (avg/count) / (double)freq.QuadPart <<endl;
	cout << "Avg. Node Time    : " << (avg/count) / (double)freq.QuadPart / (double)(dim/rfield)<<endl;

	while(1);
	return 0;
}
