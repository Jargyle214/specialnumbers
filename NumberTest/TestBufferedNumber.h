#include "UnitTest++.h"
#include "BufferedNumber.h"

using namespace luma::numbers;

SUITE(TestBufferedNumber)
{
	TEST(TestSetvalueDefaultElapsedTime)
	{
		BufferedNumber<float> n(-0.1f, -3, 3, 0.1f);

		for(int i = 0; i < 13; i++)
		{
			n.setValue(1.3f);

			CHECK_CLOSE(i / 10.0f, n.getValue(), FLOAT_THRESHOLD);
		}

	}

	TEST(TestSetvalueDefaultElapsedTime2)
	{
		BufferedNumber<float> n(0.0f, -3, 3, 0.1f);

		for(int i = 1; i < 13; i++)
		{
			n.setValue(1.3f, 1.0f);

			CHECK_CLOSE(i / 10.0f, n.getValue(), FLOAT_THRESHOLD);
		}

	}

	TEST(TestSetvalueDefaultElapsedTime0_9)
	{
		BufferedNumber<float> n(0.0f, -3, 3, 0.1f);

		for(int i = 1; i < 15; i++)
		{
			n.setValue(1.3f, 0.9f);

			CHECK_CLOSE(i / 10.0f * 0.9f, n.getValue(), FLOAT_THRESHOLD);
		}
	}

	TEST(TestSetvalueDefaultElapsedTime0_95)
	{
		BufferedNumber<float> n(0.0f, -3, 3, 0.1f);

		for(int i = 1; i < 14; i++)
		{
			n.setValue(1.3f, 0.95f);

			CHECK_CLOSE(i / 10.0f * 0.95f, n.getValue(), FLOAT_THRESHOLD);
			
		}
	}

	TEST(TestMaxChange)
	{
		BufferedNumber<float> n(0.0f, -4, 4, 0.1f);

		float previousValue = 0;

		for(int i = 0; i < 50; i++)
		{
			float v = (rand() % 100) / 20.0f - 2.5f;		

			n.setValue(v);

			CHECK_EQUAL(true, fabs(n.getValue() - previousValue) <= 0.1f + FLOAT_THRESHOLD);
			
			previousValue = n.getValue();
		}
	}

	TEST(TestMaxChangeElapsedTime94)
	{
		BufferedNumber<float> n(0.0f, -4, 4, 0.1f);

		float previousValue = 0;

		for(int i = 0; i < 50; i++)
		{
			float v = (rand() % 100) / 20.0f - 2.5f;		

			n.setValue(v, 0.94f);

			CHECK_EQUAL(true, fabs(n.getValue() - previousValue) <= 0.1f + FLOAT_THRESHOLD);
			
			previousValue = n.getValue();
		}
	}

	TEST(ForceValue)
	{
		BufferedNumber<float> n(0.0f, -4, 4, 0.1f);

		n.setValue(1.0f);
		n.setValue(1.0f);
		n.setValue(1.0f);

		n.forceValue(-1.5f);

		CHECK_CLOSE(-1.5f, n.getValue(), FLOAT_THRESHOLD);
	}

	TEST(ForceValueOutOfBounds)
	{
		BufferedNumber<float> n(0.0f, -4, 4, 0.1f);

		n.setValue(1.0f);
		n.setValue(1.0f);
		n.setValue(1.0f);

		n.forceValue(-5.0f);

		CHECK_CLOSE(-4.0f, n.getValue(), FLOAT_THRESHOLD);
	}
}