#include "UnitTest++.h"

#include "NumberTest.h"

#include "XYResponseCurve.h"

SUITE(TestXYResponseCurve)
{
	TEST(TestFindIndex)
	{
		float input[] = {0.0f, 1.0f, 3.0f};
		float output[] = {0.0f, 1.0f, 2.0f};
		
		XYResponseCurve<float, 3> f(input, output);

		CHECK_EQUAL(0u, f.findInputIndex(0.0f));
		CHECK_EQUAL(0u, f.findInputIndex(0.5f));
		CHECK_EQUAL(1u, f.findInputIndex(1.0f));
		CHECK_EQUAL(1u, f.findInputIndex(1.5f));

		CHECK_EQUAL(1u, f.findInputIndex(2.0f));
		CHECK_EQUAL(1u, f.findInputIndex(2.5f));
		CHECK_EQUAL(2u, f.findInputIndex(3.0f));
	}

	TEST(TestInterpolates)
	{
		float input[] = {0.0f, 1.0f, 3.0f};
		float output[] = {0.0f, 1.0f, 2.0f};
		
		XYResponseCurve<float, 3> f(input, output);

		CHECK_CLOSE(0.5f, f(0.5f), FLOAT_THRESHOLD);
		CHECK_CLOSE(1.5f, f(2.0f), FLOAT_THRESHOLD);
	}

	
}