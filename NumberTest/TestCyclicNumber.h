#include "UnitTest++.h"
#include "CyclicNumber.h"

SUITE(TestCyclicNumber)
{
	template <class T>
	CyclicNumber<T> makeCyclicNumber(T value, T min, T max, T increment)
	{
		return CyclicNumber<int>(value, min, max, increment);
	}

	TEST(TestConstructerValueInit)
	{
		CyclicNumber<int> c = makeCyclicNumber(2, 0, 5, 1);

		CHECK_EQUAL(2, (int) c);
	}

	TEST(TestConstructorValueCycle)
	{
		CyclicNumber<int> c = makeCyclicNumber(7, 0, 5, 1);

		CHECK_EQUAL(2, (int) c);
	}

	TEST(TestOperatorPostIncrementCycle)
	{
		CyclicNumber<int> c = makeCyclicNumber(4, 0, 5, 1);

		c++;

		CHECK_EQUAL(0, (int) c);
	}

	TEST(TestOperatorPreIncrementCycle)
	{
		CyclicNumber<int> c = makeCyclicNumber(4, 0, 5, 1);

		++c;

		CHECK_EQUAL(0, (int) c);
	}

	TEST(TestOperatorPostDecrementCycle)
	{
		CyclicNumber<int> c = makeCyclicNumber(0, 0, 5, 1);

		c--;

		CHECK_EQUAL(4, (int) c);
	}

	TEST(TestOperatorPreDecrementCycle)
	{
		CyclicNumber<int> c = makeCyclicNumber(0, 0, 5, 1);

		--c;

		CHECK_EQUAL(4, (int) c);
	}

	TEST(TestOperatorIncrementAssignCycles)
	{
		CyclicNumber<int> c = makeCyclicNumber(3, 0, 5, 1);

		c += 2;

		CHECK_EQUAL(0, (int) c);
	}

	TEST(TestOperatorDecrementAssignCycles)
	{
		CyclicNumber<int> c = makeCyclicNumber(1, 0, 5, 1);

		c -= 2;

		CHECK_EQUAL(4, (int) c);
	}

	TEST(TestOperatorAssignmentAssign)
	{
		CyclicNumber<int> c1 = makeCyclicNumber(1, 0, 5, 1);
		CyclicNumber<int> c2 = makeCyclicNumber(4, 2, 6, 2);

		c1 = c2;

		CHECK_EQUAL(c1.max(), c2.max());
		CHECK_EQUAL(c1.min(), c2.min());
		CHECK_EQUAL(c1.increment(), c2.increment());
		CHECK_EQUAL((int) c1, (int) c2);
	}
}