#include "UnitTest++.h"
#include "IntegrableNumber.h"

using namespace luma::numbers;

SUITE(TestIntegrableNumber)
{
	TEST(TestConstructorN)
	{
		IntegrableNumber<float, 3, 3> iNumber(0);

		CHECK_CLOSE(0.0f, iNumber.getValue(0), FLOAT_THRESHOLD);
	}

	TEST(TestConstructor0)
	{
		IntegrableNumber<float, 3, 0> iNumber(0);

		CHECK_CLOSE(0.0f, iNumber.getValue(0), FLOAT_THRESHOLD);
	}

	TEST(TestConstructor1)
	{
		IntegrableNumber<float, 3, 1> iNumber(0);

		CHECK_CLOSE(0.0f, iNumber.getValue(0), FLOAT_THRESHOLD);
	}

	TEST(TestGetValueOutOfBounds0)
	{
		IntegrableNumber<float, 3, 0> iNumber(0);

		iNumber.setValue(3.0f);		

		CHECK_CLOSE(0.0f, iNumber.getValue(2), FLOAT_THRESHOLD);		
		CHECK_CLOSE(0.0f, iNumber.getValue(1), FLOAT_THRESHOLD);
	}

	TEST(TestGetValueOutOfBounds1)
	{
		IntegrableNumber<float, 3, 1> iNumber(0);

		iNumber.setValue(3.0f);		

		CHECK_CLOSE(0.0f, iNumber.getValue(2), FLOAT_THRESHOLD);		
	}

	TEST(TestGetValue1)
	{
		IntegrableNumber<float, 3, 1> iNumber(0.0f);

		iNumber.setValue(1.0f);

		CHECK_CLOSE(1.0f, iNumber.getValue(0), FLOAT_THRESHOLD);
		CHECK_CLOSE(1.0f, iNumber.getValue(1), FLOAT_THRESHOLD);

		iNumber.setValue(1.0f);

		CHECK_CLOSE(1.0f, iNumber.getValue(0), FLOAT_THRESHOLD);
		CHECK_CLOSE(2.0f, iNumber.getValue(1), FLOAT_THRESHOLD);

		iNumber.setValue(1.0f);

		CHECK_CLOSE(1.0f, iNumber.getValue(0), FLOAT_THRESHOLD);
		CHECK_CLOSE(3.0f, iNumber.getValue(1), FLOAT_THRESHOLD);

		iNumber.setValue(1.0f);
		
		CHECK_CLOSE(1.0f, iNumber.getValue(0), FLOAT_THRESHOLD);
		CHECK_CLOSE(3.0f, iNumber.getValue(1), FLOAT_THRESHOLD);
	}

	TEST(TestGetValueN)
	{
		IntegrableNumber<float, 3, 3> iNumber(0.0f);

		iNumber.setValue(1.0f);

		CHECK_CLOSE(1.0f, iNumber.getValue(0), FLOAT_THRESHOLD);
		CHECK_CLOSE(1.0f, iNumber.getValue(1), FLOAT_THRESHOLD);
		CHECK_CLOSE(1.0f, iNumber.getValue(2), FLOAT_THRESHOLD);
		CHECK_CLOSE(1.0f, iNumber.getValue(3), FLOAT_THRESHOLD);

		iNumber.setValue(1.0f);

		CHECK_CLOSE(1.0f, iNumber.getValue(0), FLOAT_THRESHOLD);
		CHECK_CLOSE(2.0f, iNumber.getValue(1), FLOAT_THRESHOLD);
		CHECK_CLOSE(3.0f, iNumber.getValue(2), FLOAT_THRESHOLD);
		CHECK_CLOSE(4.0f, iNumber.getValue(3), FLOAT_THRESHOLD);

		iNumber.setValue(1.0f);

		CHECK_CLOSE(1.0f, iNumber.getValue(0), FLOAT_THRESHOLD);
		CHECK_CLOSE(3.0f, iNumber.getValue(1), FLOAT_THRESHOLD);
		CHECK_CLOSE(6.0f, iNumber.getValue(2), FLOAT_THRESHOLD);
		CHECK_CLOSE(10.0f, iNumber.getValue(3), FLOAT_THRESHOLD);

		iNumber.setValue(1.0f);
		
		CHECK_CLOSE(1.0f, iNumber.getValue(0), FLOAT_THRESHOLD);
		CHECK_CLOSE(3.0f, iNumber.getValue(1), FLOAT_THRESHOLD);
		CHECK_CLOSE(8.0f, iNumber.getValue(2), FLOAT_THRESHOLD);
		CHECK_CLOSE(17.0f, iNumber.getValue(3), FLOAT_THRESHOLD);
	}
}