#include "UnitTest++.h"
#include "PIDBufferedNumber.h"

using namespace luma::numbers;

SUITE(TestPIDBufferedNumber)
{
	TEST(TestConstructorN0)
	{
		float dFactors[] = {0.1f, 0.1f, 0.1f};
		float iFactors[] = {0.1f, 0.1f, 0.1f};

		PIDBufferedNumber<float, 3, 3, 3> pidNumber(0.0f, 0.4f, dFactors, iFactors);

		CHECK_CLOSE(0.0f, pidNumber.getValue(), FLOAT_THRESHOLD);

		pidNumber.setValue(1.0f);

		CHECK_CLOSE(1.0f, pidNumber.getValue(), FLOAT_THRESHOLD);

		pidNumber.setValue(1.0f);

		CHECK_CLOSE(1.0f, pidNumber.getValue(), FLOAT_THRESHOLD);

		pidNumber.setValue(1.0f);

		CHECK_CLOSE(2.4f, pidNumber.getValue(), FLOAT_THRESHOLD);
	}

	TEST(TestConstructorN1)
	{
		float dFactors[] = {0.1f, 0.1f, 0.1f};
		float iFactors[] = {0.2f, 0.1f, 0.1f};

		PIDBufferedNumber<float, 3, 3, 3> pidNumber(0.0f, 0.3f, dFactors, iFactors);

		CHECK_CLOSE(0.0f, pidNumber.getValue(), FLOAT_THRESHOLD);

		pidNumber.setValue(1.0f);

		CHECK_CLOSE(1.0f, pidNumber.getValue(), FLOAT_THRESHOLD);

		pidNumber.setValue(1.0f);

		CHECK_CLOSE(1.1f, pidNumber.getValue(), FLOAT_THRESHOLD);

		pidNumber.setValue(1.0f);

		CHECK_CLOSE(2.6f, pidNumber.getValue(), FLOAT_THRESHOLD);
	}

	TEST(TestConstructorN2)
	{
		float dFactors[] = {0.0f, 0.0f, 0.0f};
		float iFactors[] = {1.0f, 0.0f, 0.0f};

		PIDBufferedNumber<float, 3, 3, 3> pidNumber(0.0f, 0.0f, dFactors, iFactors);

		CHECK_CLOSE(0.0f, pidNumber.getValue(), FLOAT_THRESHOLD);

		pidNumber.setValue(1.0f);

		CHECK_CLOSE(1.0f, pidNumber.getValue(), FLOAT_THRESHOLD);

		pidNumber.setValue(1.0f);

		CHECK_CLOSE(2.0f, pidNumber.getValue(), FLOAT_THRESHOLD);

		pidNumber.setValue(1.0f);

		CHECK_CLOSE(3.0f, pidNumber.getValue(), FLOAT_THRESHOLD);
	}

	TEST(TestConstructorN3)
	{
		float dFactors[] = {1.0f, 0.0f, 0.0f};
		float iFactors[] = {0.0f, 0.0f, 0.0f};

		PIDBufferedNumber<float, 3, 3, 3> pidNumber(0.0f, 0.0f, dFactors, iFactors);

		CHECK_CLOSE(0.0f, pidNumber.getValue(), FLOAT_THRESHOLD);

		pidNumber.setValue(1.0f);

		CHECK_CLOSE(1.0f, pidNumber.getValue(), FLOAT_THRESHOLD);

		pidNumber.setValue(1.0f);

		CHECK_CLOSE(0.0f, pidNumber.getValue(), FLOAT_THRESHOLD);

		pidNumber.setValue(1.0f);

		CHECK_CLOSE(0.0f, pidNumber.getValue(), FLOAT_THRESHOLD);
	}
}