#include "UnitTest++.h"
#include "DifferentiableNumber.h"

using namespace luma::numbers;

SUITE(TestDifferentiableNumber)
{
	TEST(TestConstructor0)
	{
		DifferentiableNumber<float, 0> n(0.0f);
		
		CHECK_CLOSE(0.0f, n.getValue(0), FLOAT_THRESHOLD);		
	}

	TEST(TestConstructor1)
	{
		DifferentiableNumber<float, 1> n(0.0f);
		
		CHECK_CLOSE(0.0f, n.getValue(0), FLOAT_THRESHOLD);		
	}

	TEST(TestConstructorN)
	{
		DifferentiableNumber<float, 4> n(0.0f);
		
		CHECK_CLOSE(0.0f, n.getValue(0), FLOAT_THRESHOLD);		
	}

	TEST(TestGetValueOutOfBounds0)
	{
		DifferentiableNumber<float, 0> n(0.0f);

		n.setValue(3.0f);		

		CHECK_CLOSE(0.0f, n.getValue(2), FLOAT_THRESHOLD);		
	}

	TEST(TestGetValueOutOfBounds1)
	{
		DifferentiableNumber<float, 1> n(0.0f);

		n.setValue(3.0f);		

		CHECK_CLOSE(0.0f, n.getValue(2), FLOAT_THRESHOLD);		
	}

	TEST(TestGetValue0)
	{
		DifferentiableNumber<float, 0> n(0.0f);

		n.setValue(3.0f);		

		CHECK_CLOSE(3.0f, n.getValue(0), FLOAT_THRESHOLD);		
	}

	TEST(TestGetValue1)
	{
		DifferentiableNumber<float, 1> n(0.0f);

		n.setValue(3.0f);		

		CHECK_CLOSE(3.0f, n.getValue(0), FLOAT_THRESHOLD);		
		CHECK_CLOSE(3.0f, n.getValue(1), FLOAT_THRESHOLD);

		n.setValue(2.0f);

		CHECK_CLOSE(2.0f, n.getValue(0), FLOAT_THRESHOLD);		
		CHECK_CLOSE(-1.0f, n.getValue(1), FLOAT_THRESHOLD);
	}

	TEST(TestGetValue4)
	{
		DifferentiableNumber<float, 4> n(0.0f);

		n.setValue(3.0f, 2.0f);

		CHECK_CLOSE(3.0f, n.getValue(0), FLOAT_THRESHOLD);		
		CHECK_CLOSE(1.5f, n.getValue(1), FLOAT_THRESHOLD);
		CHECK_CLOSE(1.5f, n.getValue(2), FLOAT_THRESHOLD);
		CHECK_CLOSE(1.5f, n.getValue(3), FLOAT_THRESHOLD);
		CHECK_CLOSE(1.5f, n.getValue(4), FLOAT_THRESHOLD);

		n.setValue(2.0f, 2.0f);

		CHECK_CLOSE(2.0f, n.getValue(0), FLOAT_THRESHOLD);		
		CHECK_CLOSE(-0.5f, n.getValue(1), FLOAT_THRESHOLD);
		CHECK_CLOSE(-2.0f, n.getValue(2), FLOAT_THRESHOLD);
		CHECK_CLOSE(-3.5f, n.getValue(3), FLOAT_THRESHOLD);
		CHECK_CLOSE(-5.0f, n.getValue(4), FLOAT_THRESHOLD);

		n.setValue(4.0f, 2.0f);

		CHECK_CLOSE(4.0f, n.getValue(0), FLOAT_THRESHOLD);		
		CHECK_CLOSE(1.0f, n.getValue(1), FLOAT_THRESHOLD);
		CHECK_CLOSE(1.5f, n.getValue(2), FLOAT_THRESHOLD);
		CHECK_CLOSE(3.5f, n.getValue(3), FLOAT_THRESHOLD);
		CHECK_CLOSE(7.0f, n.getValue(4), FLOAT_THRESHOLD);

		n.setValue(6.0f, 2.0f);

		CHECK_CLOSE(6.0f, n.getValue(0), FLOAT_THRESHOLD);		
		CHECK_CLOSE(1.0f, n.getValue(1), FLOAT_THRESHOLD);
		CHECK_CLOSE(0.0f, n.getValue(2), FLOAT_THRESHOLD);
		CHECK_CLOSE(-1.5f, n.getValue(3), FLOAT_THRESHOLD);
		CHECK_CLOSE(-5.0f, n.getValue(4), FLOAT_THRESHOLD);

		n.setValue(8.0f, 2.0f);

		CHECK_CLOSE(8.0f, n.getValue(0), FLOAT_THRESHOLD);		
		CHECK_CLOSE(1.0f, n.getValue(1), FLOAT_THRESHOLD);
		CHECK_CLOSE(0.0f, n.getValue(2), FLOAT_THRESHOLD);
		CHECK_CLOSE(0.0f, n.getValue(3), FLOAT_THRESHOLD);
		CHECK_CLOSE(1.5f, n.getValue(4), FLOAT_THRESHOLD);
	}
}