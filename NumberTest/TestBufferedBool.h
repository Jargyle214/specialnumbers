#include "UnitTest++.h"
#include "BufferedBool.h"

SUITE(TestBufferedBool)
{
	TEST(TestConstructor)
	{
		BufferedBool b(0.3f, 0.7f, 0.1f);

		CHECK_EQUAL(false, b.getValue());
	}

	TEST(TestSetting)
	{
		BufferedBool b(0.2f, 0.8f, 0.1f);

		CHECK_EQUAL(false, b.getValue());
	}

	/*
		i	f	b
		0	.1	f
		1	.2	f
		2	.3	f
		3	.4	f
		4	.5	f
		5	.6	f
		6	.7	f
		++	.8	t
		
	*/
	TEST(TestSwitching)
	{
		BufferedBool b(0.3f, 0.6f, 0.1f);

		for(int i = 0; i < 6; i++)
		{
			b.setValue(true);
			CHECK_EQUAL(false, b.getValue());
		}

		b.setValue(true);
		CHECK_EQUAL(true, b.getValue());

		for(int j = 0; j < 4; j++)
		{
			b.setValue(false);
			CHECK_EQUAL(true, b.getValue());
		}

		b.setValue(false);
		CHECK_EQUAL(false, b.getValue());
	}

	TEST(TestForceValueTrue)
	{
		BufferedBool b(0.3f, 0.7f, 0.1f);

		b.forceValue(true);

		CHECK_EQUAL(true, b.getValue());
	}

	TEST(TestForceValueFalse)
	{
		BufferedBool b(0.3f, 0.7f, 0.1f);

		for(int i = 0; i < 10; i++)
			b.setValue(true);

		CHECK_EQUAL(true, b.getValue());

		b.forceValue(false);

		CHECK_EQUAL(false, b.getValue());

		b.setValue(true);

		CHECK_EQUAL(false, b.getValue());
	}

	TEST(TestSetIncrement)
	{
		BufferedBool b(0.3f, 0.7f, 0.1f);

		b.setIncrement(0.25f);

		b.setValue(true);
		b.setValue(true);
		b.setValue(true);

		CHECK_EQUAL(true, b.getValue());

	}
}