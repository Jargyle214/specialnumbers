#include "UnitTest++.h"

#define FRAME_RATE 1.0f

#include "NumberTest.h"

#include "Utils.h"

using namespace luma::numbers;

SUITE(TestUtils)
{
	TEST(TestClampInt)
	{
		CHECK_EQUAL(-2, clamp(-3, -2, 2));
		CHECK_EQUAL(-2, clamp(-2, -2, 2));
		CHECK_EQUAL(-1, clamp(-1, -2, 2));
		CHECK_EQUAL(2, clamp(2, -2, 2));
		CHECK_EQUAL(2, clamp(3, -2, 2));
	}

	TEST(TestClampFloat)
	{
		CHECK_CLOSE(-2.0f, clamp(-3.0f, -2.0f, 2.0f), FLOAT_THRESHOLD);
		CHECK_CLOSE(-2.0f, clamp(-2.0f, -2.0f, 2.0f), FLOAT_THRESHOLD);
		CHECK_CLOSE(-1.0f, clamp(-1.0f, -2.0f, 2.0f), FLOAT_THRESHOLD);
		CHECK_CLOSE(2.0f, clamp(2.0f, -2.0f, 2.0f), FLOAT_THRESHOLD);
		CHECK_CLOSE(2.0f, clamp(3.0f, -2.0f, 2.0f), FLOAT_THRESHOLD);
	}

	TEST(TestModInt)
	{
		CHECK_EQUAL(1 , mod(-5, 1, 4));
		CHECK_EQUAL(1, mod(-2, 1, 4));
		CHECK_EQUAL(3, mod(0, 1, 4));
		CHECK_EQUAL(1, mod(1, 1, 4));
		CHECK_EQUAL(3, mod(3, 1, 4));
		CHECK_EQUAL(1, mod(4, 1, 4));
		CHECK_EQUAL(2, mod(14, 1, 4));
	}

	TEST(TestModFloat)
	{
		CHECK_CLOSE(3.1f, mod(-2.9f, 1.0f, 4.0f), FLOAT_THRESHOLD); //this is unintuitive, but true (add 3 two times!)
		CHECK_CLOSE(3.9f, mod(0.9f, 1.0f, 4.0f), FLOAT_THRESHOLD);
		CHECK_CLOSE(1.9f, mod(1.9f, 1.0f, 4.0f), FLOAT_THRESHOLD);
		CHECK_CLOSE(3.9f, mod(3.9f, 1.0f, 4.0f), FLOAT_THRESHOLD);
		CHECK_CLOSE(1.9f, mod(4.9f, 1.0f, 4.0f), FLOAT_THRESHOLD);
		CHECK_CLOSE(2.9f, mod(14.9f, 1.0f, 4.0f), FLOAT_THRESHOLD);
		CHECK_CLOSE(1.0f, mod(4.0f, 1.0f, 4.0f), FLOAT_THRESHOLD);
	}


	TEST(TestReflectInt)
	{
		// -4 -3 -2 -1 0 1 2 3 4 5 6 7 8 9 10 11
		//  2  3  4  3 2 1 2 3 4 3 2 1 2 3 4  3
		//  2  3  4  5 6 1 2 3 4 5 6 1 2 3 4  5
		CHECK_EQUAL(3, reflect(-1, 1, 4));
		CHECK_EQUAL(2, reflect(-4, 1, 4));
		CHECK_EQUAL(1, reflect(1, 1, 4));
		CHECK_EQUAL(3, reflect(3, 1, 4));
		CHECK_EQUAL(4, reflect(4, 1, 4));
		CHECK_EQUAL(3, reflect(5, 1, 4));
		CHECK_EQUAL(3, reflect(11, 1, 4));

		// -4 -3 -2 -1 0 1 2 3 4 5 6 7 8 9 10 11
		//  2  3  4  5 4 3 2 3 4 5 4 3 2 3 4  5
		//  2  3  4  5 6 7 2 3 4 5 6 7 2 3 4  5
		CHECK_EQUAL(5, reflect(-1, 2, 5));
		CHECK_EQUAL(2, reflect(-4, 2, 5));
		CHECK_EQUAL(3, reflect(1, 2, 5));
		CHECK_EQUAL(3, reflect(3, 2, 5));
		CHECK_EQUAL(4, reflect(4, 2, 5));
		CHECK_EQUAL(5, reflect(5, 2, 5));
		CHECK_EQUAL(5, reflect(11, 2, 5));
		
		// -4 -3 -2 -1 0 1 2 3 4 5 6 7 8 9 10 11
		//  4  5  6  5 4 3 2 3 4 5 6 5 4 3 2  3
		//  4  5  6  7 8 9 2 3 4 5 6 7 8 9 2  3
		CHECK_EQUAL(5, reflect(-1, 2, 6));
		CHECK_EQUAL(4, reflect(-4, 2, 6));
		CHECK_EQUAL(3, reflect(1, 2, 6));
		CHECK_EQUAL(3, reflect(3, 2, 6));
		CHECK_EQUAL(4, reflect(4, 2, 6));
		CHECK_EQUAL(5, reflect(5, 2, 6));
		CHECK_EQUAL(3, reflect(11, 2, 6));
	}

	TEST(TestReflectFloat)
	{
		CHECK_CLOSE(3.1f, reflect(-1.1f, 1.0f, 4.5f), FLOAT_THRESHOLD);
		CHECK_CLOSE(2.9f, reflect(-4.1f, 1.0f, 4.5f), FLOAT_THRESHOLD);
		CHECK_CLOSE(1.1f, reflect(1.1f, 1.0f, 4.5f), FLOAT_THRESHOLD);
		CHECK_CLOSE(3.1f, reflect(3.1f, 1.0f, 4.5f), FLOAT_THRESHOLD);
		CHECK_CLOSE(4.1f, reflect(4.1f, 1.0f, 4.5f), FLOAT_THRESHOLD);
		CHECK_CLOSE(4.1f, reflect(11.1f, 1.0f, 4.5f), FLOAT_THRESHOLD);
		CHECK_CLOSE(4.4f, reflect(4.6f, 1.0f, 4.5f), FLOAT_THRESHOLD);
		CHECK_CLOSE(1.1f, reflect(0.9f, 1.0f, 4.5f), FLOAT_THRESHOLD);
	}

	TEST(TestMinReturnLeftValue)
	{
		CHECK_EQUAL(luma::numbers::min(3, 4), 3);
	}

	TEST(TestMinReturnRightValue)
	{
		CHECK_EQUAL(luma::numbers::min(4, 3), 3);
	}

	TEST(TestMaxReturnLeftValue)
	{
		CHECK_EQUAL(luma::numbers::max(3, 4), 4);
	}

	TEST(TestMaxReturnRightValue)
	{
		CHECK_EQUAL(luma::numbers::max(4, 3), 4);
	}

	TEST(TestLerpClampsBelow)
	{
		CHECK_EQUAL(10, lerp(2, 3, 5, 10, 20));
	}

	TEST(TestLerpClampsAbove)
	{
		CHECK_EQUAL(20, lerp(6, 3, 5, 10, 20));
	}

	TEST(TestLerpInterpolatesInt)
	{
		CHECK_EQUAL(15, lerp(4, 3, 5, 10, 20));
	}

	TEST(TestLerpInterpolatesFloat)
	{
		CHECK_CLOSE(15.5f, lerp(0.5f, 0.0f, 1.0f, 10.0f, 21.0f), FLOAT_THRESHOLD);
	}

	TEST(TestRampClampsBelow)
	{
		CHECK_EQUAL(10, ramp(2, 3, 5, 10, 20));
	}

	TEST(TestRampExtrapolatesAbove)
	{
		CHECK_EQUAL(25, ramp(6, 3, 5, 10, 20));
	}

	TEST(TestRampInterpolatesInt)
	{
		CHECK_EQUAL(15, ramp(4, 3, 5, 10, 20));
	}

	TEST(TestRampInterpolatesFloat)
	{
		CHECK_CLOSE(15.5f, ramp(0.5f, 0.0f, 1.0f, 10.0f, 21.0f), FLOAT_THRESHOLD);
	}
	//
	TEST(TestLineextrapolatesBelow)
	{
		CHECK_EQUAL(5, line(2, 3, 5, 10, 20));
	}

	TEST(TestLineExtrapolatesAbove)
	{
		CHECK_EQUAL(25, line(6, 3, 5, 10, 20));
	}

	TEST(TestLineInterpolatesInt)
	{
		CHECK_EQUAL(15, line(4, 3, 5, 10, 20));
	}

	TEST(TestLineInterpolatesFloat)
	{
		CHECK_CLOSE(15.5f, line(0.5f, 0.0f, 1.0f, 10.0f, 21.0f), FLOAT_THRESHOLD);
	}

	TEST(TestFrac)
	{
		CHECK_CLOSE(0.25f, frac(4.25), FLOAT_THRESHOLD);
		CHECK_CLOSE(0.75f, frac(-4.25), FLOAT_THRESHOLD);
	}

	TEST(TestFloor)
	{
		CHECK_EQUAL(4, floor(4.25));
		CHECK_EQUAL(-5, floor(-4.25));
	}

	TEST(TestExtremeIntBothLeft)
	{
		int n = extreme(1, 2, 3);
		CHECK_EQUAL(1, n);
	}

	TEST(TestExtremeIntBothRight)
	{
		int n = extreme(4, 5, 3);
		CHECK_EQUAL(5, n);
	}

	TEST(TestExtremeIntOutside)
	{
		int n = extreme(2, 5, 3);
		CHECK_EQUAL(5, n);
	}

	TEST(TestExtremeIntOutsideReversed)
	{
		int n = extreme(5, 2, 3);
		CHECK_EQUAL(5, n);
	}

	TEST(TestDefaultParameter)
	{
		int n = extreme(-5, 3);
		CHECK_EQUAL(-5, n);
	}

	TEST(TestStepBelow)
	{
		int n = step(-5, 1, -3, 4);
		CHECK_EQUAL(-3, n);
	}

	TEST(TestStepAbove)
	{
		int n = step(5, 1, -3, 4);
		CHECK_EQUAL(4, n);
	}

	TEST(TestStepThreshold)
	{
		int n = step(1, 1, -3, 4);
		CHECK_EQUAL(4, n);
	}

	TEST(TestSigmoidClampRight)
	{
		CHECK_CLOSE(4.0f, sigmoid(100.0f, -5.0f, 5.0f, -4.0f, 4.0f), FLOAT_THRESHOLD);
	}

	TEST(TestSigmoidClampLeft)
	{
		CHECK_CLOSE(-4.0f, sigmoid(-100.0f, -5.0f, 5.0f, -4.0f, 4.0f), FLOAT_THRESHOLD);
	}

	TEST(TestSigmoidZero)
	{
		CHECK_CLOSE(0.0f, sigmoid(0.0f, -5.0f, 5.0f, -4.0f, 4.0f), FLOAT_THRESHOLD);
	}
}