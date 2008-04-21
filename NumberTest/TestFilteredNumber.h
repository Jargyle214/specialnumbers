#include "UnitTest++.h"
#include "FilteredNumber.h"

using namespace luma::numbers;

SUITE(TestFilteredNumber)
{
	TEST(TestConstructor1) //just template expansion
	{
		float weights[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
		FilteredNumber<float, 10, 1> n(0.0f, weights);	
		
		float sample = 1.0f;

		for (int i = 0; i < 10; i++)
		{
			CHECK_CLOSE(sample, n.getWeight(i), FLOAT_THRESHOLD);
			sample *= 2.0f;
		}
	}

	TEST(TestGetValue1)
	{
		float weights[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
		FilteredNumber<float, 10, 1> n(0.0f, weights);	

		CHECK_CLOSE(0.0f, n.getValue(), FLOAT_THRESHOLD);
	}
	
	TEST(TestSetValue1)
	{
		float weights[] = {1, 2, 4, 8};
		FilteredNumber<float, 4, 1> n(0.0f, weights);	

		n.setValue(1);
		CHECK_CLOSE(1.0f / 15.0f, n.getValue(), FLOAT_THRESHOLD);

		n.setValue(1);
		CHECK_CLOSE(3.f / 15.0f, n.getValue(), FLOAT_THRESHOLD);

		n.setValue(1);
		CHECK_CLOSE(7.0f / 15.0f, n.getValue(), FLOAT_THRESHOLD);

		n.setValue(1);
		CHECK_CLOSE(15.0f / 15.0f, n.getValue(), FLOAT_THRESHOLD);
	}

	TEST(TestConstructor2) //just template expansion
	{
		float weights[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
		FilteredNumber<float, 10, 1> n(0.0f, weights);	
		
		float sample = 1.0f;

		for (int i = 0; i < 10; i++)
		{
			CHECK_CLOSE(sample, n.getWeight(i), FLOAT_THRESHOLD);
			sample *= 2.0f;
		}
	}

	TEST(TestGetValue2)
	{
		float weights[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
		FilteredNumber<float, 10, 1> n(0.0f, weights);	

		CHECK_CLOSE(0.0f, n.getValue(), FLOAT_THRESHOLD);
	}
	
	TEST(TestSetValue2)
	{
		float weights[] = {1, 2, 4, 8};
		FilteredNumber<float, 4, 2> n(0.0f, weights);	

		n.setValue(1);
		CHECK_CLOSE(1.0f / 15.0f, n.getValue(), FLOAT_THRESHOLD);

		n.setValue(1);
		CHECK_CLOSE(3.0f / 15.0f, n.getValue(), FLOAT_THRESHOLD);

		n.setValue(1);
		CHECK_CLOSE(7.0f / 15.0f, n.getValue(), FLOAT_THRESHOLD);

		n.setValue(1);
		CHECK_CLOSE(15.0f / 15.0f, n.getValue(), FLOAT_THRESHOLD);
	}

}