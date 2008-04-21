#include "UnitTest++.h"
#include "PIDBufferedNumber.h"
#include "IntegrableNumber.h"

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

		CHECK_CLOSE(0.748148f, pidNumber.getValue(), FLOAT_THRESHOLD);

		pidNumber.setValue(1.0f);

		CHECK_CLOSE(0.214815f, pidNumber.getValue(), FLOAT_THRESHOLD);

		pidNumber.setValue(1.0f);

		CHECK_CLOSE(0.703704f, pidNumber.getValue(), FLOAT_THRESHOLD);

		pidNumber.setValue(1.0f);

		CHECK_CLOSE(0.651852f, pidNumber.getValue(), FLOAT_THRESHOLD);

		pidNumber.setValue(1.0f);

		CHECK_CLOSE(0.685185f, pidNumber.getValue(), FLOAT_THRESHOLD);

		pidNumber.setValue(1.0f);

		CHECK_CLOSE(0.696296f, pidNumber.getValue(), FLOAT_THRESHOLD);

		pidNumber.setValue(1.0f);

		CHECK_CLOSE(0.7f, pidNumber.getValue(), FLOAT_THRESHOLD);

		for(int i = 0; i < 100; i++)
			pidNumber.setValue(1.0f);

		CHECK_CLOSE(0.7f, pidNumber.getValue(), FLOAT_THRESHOLD);
	}

	TEST(TestConstructorN1)
	{
		float dFactors[] = {0.1f, 0.1f, 0.1f};
		float iFactors[] = {0.2f, 0.1f, 0.1f};

		PIDBufferedNumber<float, 3, 3, 3> pidNumber(0.0f, 0.3f, dFactors, iFactors);

		CHECK_CLOSE(0.0f, pidNumber.getValue(), FLOAT_THRESHOLD);

		pidNumber.setValue(1.0f);

		CHECK_CLOSE(0.681482f, pidNumber.getValue(), FLOAT_THRESHOLD);

		pidNumber.setValue(1.0f);

		CHECK_CLOSE(0.181481f, pidNumber.getValue(), FLOAT_THRESHOLD);

		pidNumber.setValue(1.0f);

		CHECK_CLOSE(0.703704f, pidNumber.getValue(), FLOAT_THRESHOLD);
	}

	TEST(TestConstructorN2)
	{
		float dFactors[] = {0.0f, 0.0f, 0.0f};
		float iFactors[] = {1.0f, 0.0f, 0.0f};

		PIDBufferedNumber<float, 3, 3, 3> pidNumber(0.0f, 0.0f, dFactors, iFactors);

		CHECK_CLOSE(0.0f, pidNumber.getValue(), FLOAT_THRESHOLD);

		pidNumber.setValue(1.0f);

		CHECK_CLOSE(.333333f, pidNumber.getValue(), FLOAT_THRESHOLD);

		pidNumber.setValue(1.0f);

		CHECK_CLOSE(.6666667f, pidNumber.getValue(), FLOAT_THRESHOLD);

		pidNumber.setValue(1.0f);

		CHECK_CLOSE(1.0f, pidNumber.getValue(), FLOAT_THRESHOLD);

		pidNumber.setValue(1.0f);

		CHECK_CLOSE(1.0f, pidNumber.getValue(), FLOAT_THRESHOLD);
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

	TEST(TestIntegrator)
	{
		float iGain[] = {0.1f};
		float dGain[] = {0.0f};

		PIDBufferedNumber<float, 1, 1, 10> pidNumber(0, 0, dGain, iGain);
		IntegrableNumber<float, 10, 1> iNumber(0);

	
		for(int i = 0; i < 100; i++)
		{
			float n = (rand() % 100)/ 50.00f - 1.0f;
			pidNumber.setValue(n);
			iNumber.setValue(n);

			CHECK_CLOSE(iNumber.getValue(1) / 10, pidNumber.getValue(), FLOAT_THRESHOLD);
		}
	}

	TEST(TestForceValueToZero)
	{
		float iGain[] = {0.1f / 3.0f, 0.01f / 3.0f};
		float dGain[] = {1.0f / 3.0f};

		PIDBufferedNumber<float, 2, 2, 10> pidNumber(0, 1.0f / 3.0f, dGain, iGain);


		pidNumber.setValue(10.0);
		pidNumber.setValue(20.0);
		pidNumber.setValue(40.0);
		pidNumber.setValue(70.0);

		pidNumber.forceValue(0.0f);

		CHECK_CLOSE(0.0f, pidNumber.getValue(), FLOAT_THRESHOLD);
	}

	TEST(TestForceValueToNonZero)
	{
		float iGain[] = {0.2f, 0.2f};
		float dGain[] = {0.2f, 0.2f};

		PIDBufferedNumber<float, 2, 2, 10> pidNumber(0, 0.2f, dGain, iGain);


		pidNumber.setValue(10.0);
		pidNumber.setValue(20.0);
		pidNumber.setValue(40.0);
		pidNumber.setValue(70.0);

		pidNumber.forceValue(10.0f);

		//6.0, not 10, because the derivative terms are 0!
		CHECK_CLOSE(6.0, pidNumber.getValue(), FLOAT_THRESHOLD);
	}

	TEST(TestForceValueToNonZeroWithElapsedTime)
	{
		float iGain[] = {0.2f, 0.2f};
		float dGain[] = {0.2f, 0.2f};

		PIDBufferedNumber<float, 2, 2, 10> pidNumber(0, 0.2f, dGain, iGain);


		pidNumber.setValue(10.0);
		pidNumber.setValue(20.0);
		pidNumber.setValue(40.0);
		pidNumber.setValue(70.0);

		pidNumber.forceValue(10.0f, 33.0f);

		CHECK_CLOSE(6.0f, pidNumber.getValue(), FLOAT_THRESHOLD);
	}

	TEST(TestForceValueToZeroWithElapsedTime)
	{
		float iGain[] = {0.1f / 3.0f, 0.01f / 3.0f};
		float dGain[] = {1.0f / 3.0f};

		PIDBufferedNumber<float, 2, 2, 10> pidNumber(0, 1.0f / 3.0f, dGain, iGain);


		pidNumber.setValue(10.0);
		pidNumber.setValue(20.0);
		pidNumber.setValue(40.0);
		pidNumber.setValue(70.0);

		pidNumber.forceValue(0.0f, 33.0f);

		CHECK_CLOSE(0.0f, pidNumber.getValue(), FLOAT_THRESHOLD);
	}
}