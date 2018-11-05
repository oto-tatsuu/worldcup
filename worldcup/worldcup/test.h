#pragma once
#pragma once
#include<time.h>
#define CLOCK_PRE_SEC 1000


class Timer
{
private:
	clock_t t_start = 0;
public:
	Timer();
	~Timer();
	void Start();
	double End();
};




