#include "test.h"

Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::Start()
{
	t_start = clock();
}

double Timer::End()
{
	return (clock() - t_start) / (double)CLOCK_PRE_SEC;
}

