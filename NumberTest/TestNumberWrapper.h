#include "UnitTest++.h"
#include "NumberWrapper.h"

SUITE(TestNumberWrapper)
{
	TEST(TestConstructor)
	{
		NumberWrapper<float> n(1.34f);

		CHECK_CLOSE(1.34f, n.getValue(), FLOAT_THRESHOLD);

	}

	TEST(TestSetValue)
	{
		NumberWrapper<float> n(1.0f);

		n.setValue(1.34f, 10.0f);

		CHECK_CLOSE(1.34f, n.getValue(), FLOAT_THRESHOLD);

	}
}