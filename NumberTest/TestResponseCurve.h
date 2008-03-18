#include "UnitTest++.h"

#include "NumberTest.h"

#include "ResponseCurve.h"

SUITE(TestTransferFunction)
{
	TEST(TestClampsBelow)
	{
		float outputSamples[3] = {3.0f, 4.0f, 6.0f};
		ResponseCurve<3, float> f(1.0f, 3.0f, outputSamples);

		CHECK_CLOSE(3.0f, f(0.0f), FLOAT_THRESHOLD);
	}

	TEST(TestClampsAbove)
	{
		float outputSamples[3] = {3.0f, 4.0f, 6.0f};
		ResponseCurve<3, float> f(1.0f, 3.0f, outputSamples);

		CHECK_CLOSE(6.0f, f(4.0f), FLOAT_THRESHOLD);
	}

	TEST(TestInterpolates)
	{
		float outputSamples[3] = {3.0f, 4.0f, 6.0f};
		ResponseCurve<3, float> f(1.0f, 3.0f, outputSamples);

		CHECK_CLOSE(3.5f, f(1.5f), FLOAT_THRESHOLD);
		CHECK_CLOSE(4.0f, f(2.0f), FLOAT_THRESHOLD);
		CHECK_CLOSE(5.0f, f(2.5f), FLOAT_THRESHOLD);
	}
}