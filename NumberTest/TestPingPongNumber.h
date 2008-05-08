#include "UnitTest++.h"
#include "PingPongNumber.h"

SUITE(TestPingPongNumber)
{
	TEST(TestConstructorValueInit)
	{
		PingPongNumber<int> p = PingPongNumber<int>(2, 0, 5, 1);

		CHECK_EQUAL(2, p.getValue());
	}

	TEST(TestConstructorValueInit2)
	{
		PingPongNumber<int> p = PingPongNumber<int>(5, 2, 5, 1);

		CHECK_EQUAL(3, p.getValue());
	}

	TEST(TestCyclicValue) //white box test
	{
		PingPongNumber<int> p = PingPongNumber<int>(2, 2, 5, 1);
		
		CHECK_EQUAL(2, p.getCyclicValue());

		p++;
		CHECK_EQUAL(3, p.getCyclicValue());

		p++;
		CHECK_EQUAL(4, p.getCyclicValue());

		p++;
		CHECK_EQUAL(5, p.getCyclicValue());

		p++;
		CHECK_EQUAL(2, p.getCyclicValue());

		p++;
		CHECK_EQUAL(3, p.getCyclicValue());

		p++;
		CHECK_EQUAL(4, p.getCyclicValue());

		p++;
		CHECK_EQUAL(5, p.getCyclicValue());
	}

	TEST(TestGetValue)
	{
		PingPongNumber<int> p = PingPongNumber<int>(2, 2, 5, 1);
		
		CHECK_EQUAL(2,p.getValue());

		p++;
		CHECK_EQUAL(3, p.getValue());

		p++;
		CHECK_EQUAL(4, p.getValue());

		p++;
		CHECK_EQUAL(3, p.getValue());

		p++;
		CHECK_EQUAL(2, p.getValue());

		p++;
		CHECK_EQUAL(3, p.getValue());

		p++;
		CHECK_EQUAL(4, p.getValue());

		p++;
		CHECK_EQUAL(3, p.getValue());
	}

	TEST(TestSetIncrementGetCyclicValue)
	{
		PingPongNumber<int> p = PingPongNumber<int>(2, 0, 5, 2);

		p.setIncrement(1);
		
		CHECK_EQUAL(2, p.getCyclicValue());

		p++;
		CHECK_EQUAL(3, p.getCyclicValue());

		p++;
		CHECK_EQUAL(4, p.getCyclicValue());

		p++;
		CHECK_EQUAL(5, p.getCyclicValue());

		p++;
		CHECK_EQUAL(6, p.getCyclicValue());

		p++;
		CHECK_EQUAL(7, p.getCyclicValue());

		p++;
		CHECK_EQUAL(0, p.getCyclicValue());

		p++;
		CHECK_EQUAL(1, p.getCyclicValue());
	}

	TEST(TestSetIncrement)
	{
		PingPongNumber<int> p = PingPongNumber<int>(2, 0, 5, 2);

		p.setIncrement(1);
		
		//2
		CHECK_EQUAL(2, p.getValue());

		p++;//3
		CHECK_EQUAL(3, p.getValue());

		p++;//4
		CHECK_EQUAL(4, p.getValue());

		p++;//5
		CHECK_EQUAL(3, p.getValue());

		p++;//6
		CHECK_EQUAL(2, p.getValue());

		p++;//7
		CHECK_EQUAL(1, p.getValue());

		p++;//0
		CHECK_EQUAL(0, p.getValue());

		p++;
		CHECK_EQUAL(1, p.getValue());
	}

	/*TEST(TestP)
	{
		PingPongNumber<float> p(0.0f, 0.0f, 1.0f, 0.02f);

		for(int i = 0; i < 100; i++)
		{
			p++;

			printf("%f ", (float) p);
		}
	}*/
}
