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
		CHECK_CLOSE(0.333333f, iNumber.getValue(1), FLOAT_THRESHOLD);

		iNumber.setValue(1.0f);

		CHECK_CLOSE(1.0f, iNumber.getValue(0), FLOAT_THRESHOLD);
		CHECK_CLOSE(.666667, iNumber.getValue(1), FLOAT_THRESHOLD);

		iNumber.setValue(1.0f);

		CHECK_CLOSE(1.0f, iNumber.getValue(0), FLOAT_THRESHOLD);
		CHECK_CLOSE(1.0f, iNumber.getValue(1), FLOAT_THRESHOLD);

		iNumber.setValue(1.0f);
		
		CHECK_CLOSE(1.0f, iNumber.getValue(0), FLOAT_THRESHOLD);
		CHECK_CLOSE(1.0f, iNumber.getValue(1), FLOAT_THRESHOLD);
	}

	TEST(TestGetValue1Var)
	{
		IntegrableNumber<float, 3, 1> iNumber(0.0f);

		iNumber.setValue(1.0f);

		CHECK_CLOSE(1.0f, iNumber.getValue(0), FLOAT_THRESHOLD);
		CHECK_CLOSE(.33333f, iNumber.getValue(1), FLOAT_THRESHOLD);

		iNumber.setValue(0.5f);

		CHECK_CLOSE(0.5f, iNumber.getValue(0), FLOAT_THRESHOLD);
		CHECK_CLOSE(0.5f, iNumber.getValue(1), FLOAT_THRESHOLD);

		iNumber.setValue(0.2f);

		CHECK_CLOSE(0.2f, iNumber.getValue(0), FLOAT_THRESHOLD);
		CHECK_CLOSE(0.566667f, iNumber.getValue(1), FLOAT_THRESHOLD);

		iNumber.setValue(0.1f);
		
		CHECK_CLOSE(0.1f, iNumber.getValue(0), FLOAT_THRESHOLD);
		CHECK_CLOSE(0.26667f, iNumber.getValue(1), FLOAT_THRESHOLD);
		
		iNumber.setValue(0.3f);

		CHECK_CLOSE(0.3f, iNumber.getValue(0), FLOAT_THRESHOLD);
		CHECK_CLOSE(0.2f, iNumber.getValue(1), FLOAT_THRESHOLD);
	}

	TEST(TestGetValueN)
	{
		IntegrableNumber<float, 3, 3> iNumber(0.0f);

		iNumber.setValue(1.0f);

		CHECK_CLOSE(1.0f, iNumber.getValue(0), FLOAT_THRESHOLD);
		CHECK_CLOSE(0.333333f, iNumber.getValue(1), FLOAT_THRESHOLD);
		CHECK_CLOSE(0.111111f, iNumber.getValue(2), FLOAT_THRESHOLD);
		CHECK_CLOSE(0.037037f, iNumber.getValue(3), FLOAT_THRESHOLD);

		iNumber.setValue(1.0f);

		CHECK_CLOSE(1.0f, iNumber.getValue(0), FLOAT_THRESHOLD);
		CHECK_CLOSE(0.666667f, iNumber.getValue(1), FLOAT_THRESHOLD);
		CHECK_CLOSE(0.333333f, iNumber.getValue(2), FLOAT_THRESHOLD);
		CHECK_CLOSE(0.148148f, iNumber.getValue(3), FLOAT_THRESHOLD);

		iNumber.setValue(1.0f);

		CHECK_CLOSE(1.0f, iNumber.getValue(0), FLOAT_THRESHOLD);
		CHECK_CLOSE(1.0f, iNumber.getValue(1), FLOAT_THRESHOLD);
		CHECK_CLOSE(0.666667f, iNumber.getValue(2), FLOAT_THRESHOLD);
		CHECK_CLOSE(0.37037f, iNumber.getValue(3), FLOAT_THRESHOLD);

		iNumber.setValue(1.0f);
		
		CHECK_CLOSE(1.0f, iNumber.getValue(0), FLOAT_THRESHOLD);
		CHECK_CLOSE(1.0f, iNumber.getValue(1), FLOAT_THRESHOLD);
		CHECK_CLOSE(0.8888889f, iNumber.getValue(2), FLOAT_THRESHOLD);
		CHECK_CLOSE(0.62963f, iNumber.getValue(3), FLOAT_THRESHOLD);

		iNumber.setValue(1.0f);
		
		CHECK_CLOSE(1.0f, iNumber.getValue(0), FLOAT_THRESHOLD);
		CHECK_CLOSE(1.0f, iNumber.getValue(1), FLOAT_THRESHOLD);
		CHECK_CLOSE(1.0f, iNumber.getValue(2), FLOAT_THRESHOLD);
		CHECK_CLOSE(0.851852f, iNumber.getValue(3), FLOAT_THRESHOLD);

		iNumber.setValue(1.0f);
		
		CHECK_CLOSE(1.0f, iNumber.getValue(0), FLOAT_THRESHOLD);
		CHECK_CLOSE(1.0f, iNumber.getValue(1), FLOAT_THRESHOLD);
		CHECK_CLOSE(1.0f, iNumber.getValue(2), FLOAT_THRESHOLD);
		CHECK_CLOSE(0.962963f, iNumber.getValue(3), FLOAT_THRESHOLD);
				
		iNumber.setValue(1.0f);
		
		CHECK_CLOSE(1.0f, iNumber.getValue(0), FLOAT_THRESHOLD);
		CHECK_CLOSE(1.0f, iNumber.getValue(1), FLOAT_THRESHOLD);
		CHECK_CLOSE(1.0f, iNumber.getValue(2), FLOAT_THRESHOLD);
		CHECK_CLOSE(1.0f, iNumber.getValue(3), FLOAT_THRESHOLD);

	}

#define SAMPLE_COUNT 10

	TEST(TestSamples)
	{		
		IntegrableNumber<float, SAMPLE_COUNT, 1> iNumber(0.0f);
		
		for(int j = 0; j < SAMPLE_COUNT; j++)
		{
			//printf("%f ", iNumber.getSample(j + 1));
			CHECK_CLOSE(0.0f, iNumber.getSample(j + 1), FLOAT_THRESHOLD);
		}
		
		//printf("\n");
		//printf("*****\n");

		for(int i = 0; i < 10; i++)
		{			

			for(int j = 0; j < SAMPLE_COUNT; j++)
			{
				//printf("%f ", iNumber.getSample(j + 1));
				CHECK_CLOSE(j < i ? 0.1f : 0.0f, iNumber.getSample(j + 1), FLOAT_THRESHOLD);
			}

			iNumber.setValue(0.1f);
			//printf("\n");
			//printf("*****\n");
		}
	}

	TEST(forceValue0)
	{
		IntegrableNumber<float, SAMPLE_COUNT, 0> iNumber(0.0f);

		iNumber.setValue(10);
		
		iNumber.forceValue(0.0f, 10.0f);

		CHECK_CLOSE(0.0f, iNumber.getValue(0), FLOAT_THRESHOLD);
		
		iNumber.setValue(30);

		iNumber.forceValue(10.0f);

		CHECK_CLOSE(10.0f, iNumber.getValue(0), FLOAT_THRESHOLD);		
	}

	TEST(forceValue1)
	{
		IntegrableNumber<float, SAMPLE_COUNT, 1> iNumber(0.0f);

		iNumber.setValue(10);
		iNumber.setValue(20);
		iNumber.setValue(30);

		iNumber.forceValue(0.0f);

		CHECK_CLOSE(0.0f, iNumber.getValue(0), FLOAT_THRESHOLD);
		CHECK_CLOSE(0.0f, iNumber.getValue(1), FLOAT_THRESHOLD);
		

		iNumber.setValue(10);
		iNumber.setValue(20);
		iNumber.setValue(30);

		//iNumber.forceValue(10.0f);

		for(int i = 0; i < 100; i++)
			iNumber.setValue(10.0f);

		CHECK_CLOSE(10.0f, iNumber.getValue(0), FLOAT_THRESHOLD);
		CHECK_CLOSE(10.0f, iNumber.getValue(1), FLOAT_THRESHOLD);		
	}

		TEST(forceValue1WithElapsedTime)
	{
		IntegrableNumber<float, SAMPLE_COUNT, 1> iNumber(0.0f);

		iNumber.setValue(10);
		iNumber.setValue(20);
		iNumber.setValue(30);

		iNumber.forceValue(0.0f, 10.0f);

		CHECK_CLOSE(0.0f, iNumber.getValue(0), FLOAT_THRESHOLD);
		CHECK_CLOSE(0.0f, iNumber.getValue(1), FLOAT_THRESHOLD);
		

		iNumber.setValue(10);
		iNumber.setValue(20);
		iNumber.setValue(30);

		iNumber.forceValue(10.0f, 33.0f);

		CHECK_CLOSE(10.0, iNumber.getValue(0), FLOAT_THRESHOLD);
		CHECK_CLOSE(10.0f, iNumber.getValue(1), FLOAT_THRESHOLD);		
	}
	
	TEST(TestForceValue2)
	{
		IntegrableNumber<float, SAMPLE_COUNT, 2> iNumber(0.0f);

		iNumber.setValue(10);
		iNumber.setValue(20);
		iNumber.setValue(30);

		iNumber.forceValue(0.0f);

		CHECK_CLOSE(0.0f, iNumber.getValue(0), FLOAT_THRESHOLD);
		CHECK_CLOSE(0.0f, iNumber.getValue(1), FLOAT_THRESHOLD);
		CHECK_CLOSE(0.0f, iNumber.getValue(2), FLOAT_THRESHOLD);

		iNumber.setValue(10);
		iNumber.setValue(20);
		iNumber.setValue(30);

		iNumber.forceValue(10.0f);

		CHECK_CLOSE(10.0f, iNumber.getValue(0), FLOAT_THRESHOLD);
		CHECK_CLOSE(10.0f, iNumber.getValue(1), FLOAT_THRESHOLD);
		CHECK_CLOSE(10.0f, iNumber.getValue(2), FLOAT_THRESHOLD);
	}

	TEST(TestForceValue2WithElapsedTime)
	{
		IntegrableNumber<float, SAMPLE_COUNT, 2> iNumber(0.0f);

		iNumber.setValue(10);
		iNumber.setValue(20);
		iNumber.setValue(30);

		iNumber.forceValue(0.0f, 33.0f);

		CHECK_CLOSE(0.0f, iNumber.getValue(0), FLOAT_THRESHOLD);
		CHECK_CLOSE(0.0f, iNumber.getValue(1), FLOAT_THRESHOLD);
		CHECK_CLOSE(0.0f, iNumber.getValue(2), FLOAT_THRESHOLD);

		iNumber.setValue(10);
		iNumber.setValue(20);
		iNumber.setValue(30);

		iNumber.forceValue(10.0f, 33.0f);

		CHECK_CLOSE(10.0f, iNumber.getValue(0), FLOAT_THRESHOLD);
		CHECK_CLOSE(10.0f, iNumber.getValue(1), FLOAT_THRESHOLD);
		CHECK_CLOSE(10.0f, iNumber.getValue(2), FLOAT_THRESHOLD);
	}	
}