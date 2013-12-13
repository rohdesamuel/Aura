#ifndef TIMER__H
#define TIMER__H

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <windows.h>
#include <stdio.h>

class Timer
{
public:
	Timer(std::string filename):filename(filename),count_(0), avg_(0){
		QueryPerformanceFrequency(&freq_);
	}

	inline void start(){
		QueryPerformanceCounter(&start_);
	};

	inline void stop(){
		QueryPerformanceCounter(&end_);
		avg_ += end_.QuadPart - start_.QuadPart;
		++count_;
	};

	inline void reset(){
		start_ = end_ = freq_ = LARGE_INTEGER();
		avg_ = 0;
		count_ = 0;
	};

	inline void hardStart(){
		start_ = end_ = LARGE_INTEGER();
		avg_ = 0;
		count_ = 0;
		QueryPerformanceFrequency(&freq_);
		QueryPerformanceCounter(&start_);
	};

	void overwrite_stats(){
		  FILE * file;
		  fopen_s(&file, filename.c_str(), "w");
		  if (file != NULL)
		  {
			  fprintf(file,"%I64 %I64 %I64\n", start_.QuadPart, end_.QuadPart, freq_.QuadPart);
			  fprintf(file,"%d %f\n",count_,avg_);
			  fprintf(file,"Average Clock Cycles: %f\n", (avg_/count_));
			  fprintf(file,"Average Time: %f\n", (avg_/count_) / (double)freq_.QuadPart);
			  fclose(file);
		  }
	};

	void append_stats(){
		  FILE * file;
		  fopen_s(&file, filename.c_str(), "a");
		  if (file != NULL)
		  {
			  fprintf(file,"%I64 %I64 %I64\n", start_.QuadPart, end_.QuadPart, freq_.QuadPart);
			  fprintf(file,"%d %f\n",count_,avg_);
			  fprintf(file,"Average Clock Cycles: %f\n", (avg_/count_));
			  fprintf(file,"Average Time: %f\n", (avg_/count_) / (double)freq_.QuadPart);
			  fclose(file);
		  }
	};

	double average_time(){
		if (count_ != 0 && freq_.QuadPart != 0)
			return (avg_/count_) / (double)freq_.QuadPart;
		return 0;
	};

	double average_cycles(){
		if (count_ != 0)
			return avg_/count_;
		return 0;
	};
private:
	LARGE_INTEGER start_, end_, freq_;
	int count_;
	double avg_;
	std::string filename;
};

#endif