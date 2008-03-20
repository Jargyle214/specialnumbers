#include "UnitTest++.h"
#include "PeriodicResponseCurve.h"

SUITE(TestPeriodicResponseCurve)
{
	TEST(TestPeriodicResponseCurveConstructor)
	{
		float samples[] = {1.0f, 2.0f, 4.0f};

		PeriodicResponseCurve<float, 3> curve(0.0f, 1.0f, samples);

		CHECK_CLOSE(0.0f, curve.getInputMin(), FLOAT_THRESHOLD);
		CHECK_CLOSE(1.0f, curve.getInputMax(), FLOAT_THRESHOLD);
	}

	TEST(TestGetValueInRange)
	{
		float samples[] = {1.0f, 2.0f, 4.0f};

		PeriodicResponseCurve<float, 3> curve(0.0f, 1.0f, samples);

		CHECK_CLOSE(1.5f, curve(0.25f), FLOAT_THRESHOLD);
		CHECK_CLOSE(3.0f, curve(0.75f), FLOAT_THRESHOLD);
	}

	TEST(TestGetValueOfPeriodsAbove)
	{
		float samples[] = {1.0f, 2.0f, 4.0f};

		PeriodicResponseCurve<float, 3> curve(0.0f, 1.0f, samples);

		CHECK_CLOSE(curve(0.25f), curve(1.25f), FLOAT_THRESHOLD);
		CHECK_CLOSE(curve(0.25f), curve(2.25f), FLOAT_THRESHOLD);


		CHECK_CLOSE(curve(0.75f), curve(1.75f), FLOAT_THRESHOLD);
		CHECK_CLOSE(curve(0.75f), curve(2.75f), FLOAT_THRESHOLD);
	}

	TEST(TestGetValueOfPeriodsBelow)
	{
		float samples[] = {1.0f, 2.0f, 4.0f};

		PeriodicResponseCurve<float, 3> curve(0.0f, 1.0f, samples);

		CHECK_CLOSE(curve(0.25f), curve(-0.75f), FLOAT_THRESHOLD);
		CHECK_CLOSE(curve(0.25f), curve(-1.75f), FLOAT_THRESHOLD);


		CHECK_CLOSE(curve(0.75f), curve(-0.25f), FLOAT_THRESHOLD);
		CHECK_CLOSE(curve(0.75f), curve(-1.25f), FLOAT_THRESHOLD);
	}

	TEST(TestGetValueOfBorders)
	{
		float samples[] = {1.0f, 2.0f, 4.0f};

		PeriodicResponseCurve<float, 3> curve(0.0f, 1.0f, samples);

		CHECK_CLOSE(1.0f, curve(0.0f), FLOAT_THRESHOLD);
		CHECK_CLOSE(1.0f, curve(4.0f), FLOAT_THRESHOLD);
		CHECK_CLOSE(4.0f, curve(3.99999f), FLOAT_THRESHOLD);


		CHECK_CLOSE(curve(0.75f), curve(-0.25f), FLOAT_THRESHOLD);
		CHECK_CLOSE(curve(0.75f), curve(-1.25f), FLOAT_THRESHOLD);
	}

}