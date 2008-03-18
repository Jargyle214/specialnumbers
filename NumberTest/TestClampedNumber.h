#include "UnitTest++.h"
#include "ClampedNumber.h"


/* 
	Note: ClampedNumber serves as the model for RangedNumber. RangedNumber cannot
	be constructed directly, since it is abstract. Therefor many of RangedNumbers 
	methods are tested by using ClampedNumber.
*/
SUITE(TestClampedNumber)
{
	TEST(TestConstructorValueInit)
	{
		ClampedNumber<int> c(3, 1, 5, 1);
		CHECK_EQUAL(3, (int) c);
	}

	TEST(TestConstructorClampBottom)
	{
		ClampedNumber<int> c(0, 1, 5, 1);
		CHECK_EQUAL(1, (int) c);
	}

	TEST(TestConstructorClampTop)
	{
		ClampedNumber<int> c(7, 1, 5, 1);
		CHECK_EQUAL(4, (int) c);
	}

	TEST(TestCopyConstructorValueInit)
	{
		ClampedNumber<int> c1(4, 1, 5, 1);
		ClampedNumber<int> c2(c1);

		CHECK_EQUAL( (int)c1, (int)c2);
	}

	TEST(TestCopyConstructorMinInit)
	{
		ClampedNumber<int> c1(4, 1, 5, 1);
		ClampedNumber<int> c2(c1);

		CHECK_EQUAL( c1.min(), c2.min());
	}

	TEST(TestCopyConstructorMaxInit)
	{
		ClampedNumber<int> c1(4, 1, 5, 1);
		ClampedNumber<int> c2(c1);

		CHECK_EQUAL( c1.max(), c2.max());
	}

	TEST(TestCopyConstructorIncrementInit)
	{
		ClampedNumber<int> c1(4, 1, 5, 1);
		ClampedNumber<int> c2(c1);

		CHECK_EQUAL( c1.increment(), c2.increment());
	}

	TEST(TestAssignmentAssignValue)
	{
		ClampedNumber<int> c1(3, 1, 5, 1);
		ClampedNumber<int> c2(30, 2, 50, 2);

		c1 = c2;

		CHECK_EQUAL((int) c1,(int) c2);
	}

	TEST(TestAssignmentAssignMin)
	{
		ClampedNumber<int> c1(3, 1, 5, 1);
		ClampedNumber<int> c2(30, 2, 50, 2);

		c1 = c2;

		CHECK_EQUAL(c1.min(), c2.min());
	}

	TEST(TestAssignmentAssignMax)
	{
		ClampedNumber<int> c1(3, 1, 5, 1);
		ClampedNumber<int> c2(30, 2, 50, 2);

		c1 = c2;

		CHECK_EQUAL(c1.max(), c2.max());
	}

	TEST(TestAssignmentAssignIncrement)
	{
		ClampedNumber<int> c1(3, 1, 5, 1);
		ClampedNumber<int> c2(30, 2, 50, 2);

		c1 = c2;

		CHECK_EQUAL(c1.increment(), c2.increment());
	}

	TEST(TestOperatorIncrementInt)
	{
		ClampedNumber<int> c(1, 1, 5, 1);

		for(int i = 1; i < 4; i++)
		{
			c++;
			CHECK_EQUAL(i+1, (int) c);
		}

		c++;
		CHECK_EQUAL(4, (int) c);
	}

	TEST(TestOperatorIncrementFloat)
	{
		ClampedNumber<float> c(0.1f, 0.1f, 0.5f, 0.1f);

		for(float i = 0.1f; i < 0.4f; i += 0.1f)
		{
			c++;
			CHECK_CLOSE(i + 0.1f, (float) c, FLOAT_THRESHOLD);
		}

		c++;
		CHECK_CLOSE(0.4f, (float) c, FLOAT_THRESHOLD);
	}

	TEST(TestIncrement)
	{
		ClampedNumber<float> c(0.0f, 0.3f, 0.7f, 0.1f);

		c.setIncrement(0.2f);
		CHECK_CLOSE(0.2f, c.increment(), FLOAT_THRESHOLD);

	}

	TEST(TestSetIncrementClamps)
	{
		ClampedNumber<int> c(9, 0, 10, 1);

		c.setIncrement(2);
		CHECK_EQUAL(8, (int) c);
	}
}