#include "UnitTest++.h"
#include "BufferedState.h"

SUITE(TestBufferedState)
{
	TEST(TestConstructorInitState)
	{
		float thresholds[3] = {0.7f, 0.7f, 0.7f};
		float stateValues[3] = {0.0f, 1.0f, 0.0f};

		BufferedState<3> b(1, stateValues, thresholds, 0.1f);

		CHECK_EQUAL(1u, b.getValue());
	}

	TEST(TestStateTransition)
	{
		float thresholds[3] = {0.6f, 0.6f, 0.6f};
		float stateValues[3] = {1.0f, 0.0f, 0.0f};

		BufferedState<3> b(0, stateValues, thresholds, 0.1f);

		for(int i = 0; i < 6; i++)
		{
			b.setValue(2);
			CHECK_EQUAL(0u, b.getValue());
		}

		b.setValue(2);
		CHECK_EQUAL(2u, b.getValue());
	}

	TEST(TestCopyConstructorInitState)
	{
		float thresholds[3] = {0.6f, 0.6f, 0.6f};
		float stateValues[3] = {0.0f, 1.0f, 0.0f};

		BufferedState<3> b1(1, stateValues, thresholds, 0.1f);
		BufferedState<3> b2(b1);

		CHECK_EQUAL(1u, b2.getValue());
	}

	TEST(TestCopyConstructorCopiesThresholds)
	{
		float thresholds[3] = {0.6f, 0.6f, 0.6f};
		float stateValues[3] = {0.0f, 1.0f, 0.0f};

		BufferedState<3> b1(1, stateValues, thresholds, 0.1f);
		BufferedState<3> b2(b1);

		for(int i = 0; i < 10; i++)
		{
			b1.setValue(2);
			b2.setValue(2);

			CHECK_EQUAL(b1.getValue(), b2.getValue());
		}
	}

	TEST(TestCopyConstructorCopiesStates)
	{
		float thresholds[3] = {0.6f, 0.6f, 0.6f};
		float stateValues[3] = {0.0f, 1.0f, 0.5f};

		BufferedState<3> b1(1, stateValues, thresholds, 0.1f);
		BufferedState<3> b2(b1);

		for(int i = 0; i < 10; i++)
		{
			b1.setValue(2);
			b2.setValue(2);

			CHECK_EQUAL(b1.getValue(), b2.getValue());
		}
	}

	TEST(TestConstructorInitIncrement)
	{
		float thresholds[3] = {0.6f, 0.6f, 0.6f};
		float stateValues[3] = {1.0f, 0.0f, 0.0f};

		BufferedState<3> b(0, stateValues, thresholds, 0.2f);

		for(int i = 0; i < 3; i++)
		{
			b.setValue(2);
			CHECK_EQUAL(0u, b.getValue());
		}

		b.setValue(2);
		CHECK_EQUAL(2u, b.getValue());
	}

	TEST(TestConstructorInitStateValues)
	{
		float thresholds[3] = {0.6f, 0.6f, 0.6f};
		float stateValues[3] = {1.0f, 0.0f, 0.5f};

		BufferedState<3> b(0, stateValues, thresholds, 0.2f);

		b.setValue(2);
		CHECK_EQUAL(2u, b.getValue());
	}

	TEST(TestForceState)
	{
		float thresholds[3] = {0.6f, 0.6f, 0.6f};
		float stateValues[3] = {1.0f, 0.0f, 0.0f};

		BufferedState<3> b(0, stateValues, thresholds, 0.2f);

		b.forceValue(2);
		CHECK_EQUAL(2u, b.getValue());
	}

	TEST(TestForceStateSetStateValues)
	{
		float thresholds[3] = {0.6f, 0.6f, 0.6f};
		float stateValues[3] = {1.0f, 0.0f, 0.0f};

		printf("************************");

		BufferedState<3> b(0, stateValues, thresholds, 0.2f);

		b.forceValue(2);
		b.setValue(0);
		CHECK_EQUAL(2u, b.getValue());
	}


}