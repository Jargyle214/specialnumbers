#include "UnitTest++.h"
#include "ClampedNumber.h"

#include <time.h>
#include <iostream>

using namespace std;

#define LOOP_ITERATIONS 10000000

#define SLOW 150

#define CHECK_TIME(t1, t2, factor) CHECK( ((t1) + 1) <= (factor)*((t2) + 1)) 

SUITE(TestClampedNumberPerformance)
{
	int getMilliSeconds()
	{
		return (int)(((float) clock() / (float) CLOCKS_PER_SEC) * 1000.0f);
	}

	TEST(TestConstructor)
	{

		unsigned int benchmarkStart = getMilliSeconds();

		int sum = 0;

		for(unsigned int i = 0; i < LOOP_ITERATIONS; i++)
		{
			int n = 1;
			
			sum += n;
		}

		unsigned int benchmarkEnd = getMilliSeconds();
		unsigned int benchmarkElapsed = benchmarkEnd - benchmarkStart;

		unsigned int testStart = getMilliSeconds();

		sum = 0;
		for(unsigned int i = 0; i < LOOP_ITERATIONS; i++)
		{	
			ClampedNumber<int> n(1, 0, 10, 1);
			sum += (int)n;
		}

		unsigned int testEnd = getMilliSeconds();

		unsigned int testElapsed = testEnd - testStart;

		CHECK_TIME(testElapsed, benchmarkElapsed, SLOW);		
	}

	TEST(TestAssignement)
	{

		unsigned int benchmarkStart = getMilliSeconds();

		int sum = 0;

		for(unsigned int i = 0; i < LOOP_ITERATIONS; i++)
		{
			int n = 1;
			
			sum += n;
		}

		unsigned int benchmarkEnd = getMilliSeconds();
		unsigned int benchmarkElapsed = benchmarkEnd - benchmarkStart;

		unsigned int testStart = getMilliSeconds();

		sum = 0;
		ClampedNumber<int> n(0, 0, 10, 1);
		for(unsigned int i = 0; i < LOOP_ITERATIONS; i++)
		{	
			n = 1;
			sum += (int)n;
		}

		unsigned int testEnd = getMilliSeconds();

		unsigned int testElapsed = testEnd - testStart;

		CHECK_TIME(testElapsed, benchmarkElapsed, SLOW);		
	}
}