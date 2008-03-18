#include "UnitTest++.h"
#include "PingPongNumber.h"

SUITE(TestPingPongNumber)
{
	template <class T>
	PingPongNumber<T> makePingPongNumber(T value, T min, T max, T increment)
	{
		return PingPongNumber<T>(value, min, max, increment);
	}

	TEST(TestConstructorValueInit)
	{
		PingPongNumber<int> p = makePingPongNumber(2, 0, 5, 1);

		CHECK_EQUAL(2, (int) p);
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
