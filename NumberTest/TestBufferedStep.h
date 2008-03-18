#include "UnitTest++.h"
#include "BufferedStep.h"

SUITE(TestBufferedStep)
{
	TEST(TestConstructor)
	{
		float upwardsThresholds[] = {0.7f, 1.7f};
		float downwardsThresholds[] = {0.3f, 1.3f};

		BufferedStep<3> b(0.0f, 2.0f, upwardsThresholds, downwardsThresholds, 0.1f);

		CHECK_EQUAL(0u, b.getState());
	}

	TEST(TestBufferedBoolEquivalence)
	{
		float upwardsThresholds[] = {0.7f};
		float downwardsThresholds[] = {0.3f};

		BufferedStep<2> bStep(0.0f, 1.0f, upwardsThresholds, downwardsThresholds, 0.1f);
		BufferedBool bBool(0.3f, 0.7f, 0.1f);

		for(int i = 0; i < 9; i++)
		{
			bStep.setStateUp(true); 
			bBool.setValue(true);
			
			CHECK_EQUAL(bBool.getValue(), bStep.getState() == 1);
		}

		for(int i = 8; i > 0; i--)
		{
			bStep.setStateUp(false);
		    bBool.setValue(false);

			CHECK_EQUAL(bBool.getValue(), bStep.getState() == 1);
		}
	}

	TEST(ChainedBufferedBoolEquivalence)
	{
		float upwardsThresholds[] = {0.7f, 1.7f};
		float downwardsThresholds[] = {0.3f, 1.3f};

		BufferedStep<3> bStep(0.0f, 2.0f, upwardsThresholds, downwardsThresholds, 0.1f);
		BufferedBool bBool1(0.3f, 0.7f, 0.1f);
		BufferedBool bBool2(0.3f, 0.7f, 0.1f);

		for(int i = 0; i < 20; i++)
		{
			bStep.setStateUp(true); 

			if(i < 10)
			{
				bBool1.setValue(true);
				CHECK_EQUAL(bBool1.getValue(), bStep.getState() == 1);
			}
			else
			{
				bBool2.setValue(true);
				CHECK_EQUAL(bBool2.getValue(), bStep.getState() == 2);
			}
		}
 
		for(int i = 20; i > 0; i--)
		{
			bStep.setStateUp(false);

			if(i > 10)
			{
				bBool2.setValue(false);
				CHECK_EQUAL(bBool2.getValue(), bStep.getState() == 2);
			}
			else
			{
				bBool1.setValue(false);
				CHECK_EQUAL(bBool1.getValue(), bStep.getState() == 1);
			}
		}
	}
	
	TEST(ChainedBufferedBoolEquivalence2)
	{
		float upwardsThresholds[] = {0.7f, 1.7f};
		float downwardsThresholds[] = {0.3f, 1.3f};

		BufferedStep<3> bStep(0.0f, 2.0f, upwardsThresholds, downwardsThresholds, 0.1f);
		BufferedBool bBool1(0.3f, 0.7f, 0.1f);
		BufferedBool bBool2(0.3f, 0.7f, 0.1f);

		for(int i = 0; i < 8; i++)
		{
			bStep.setStateUp(true); 

			if(i < 10)
			{
				bBool1.setValue(true);
				CHECK_EQUAL(bBool1.getValue(), bStep.getState() == 1);
			}
			else
			{
				bBool2.setValue(true);
				CHECK_EQUAL(bBool2.getValue(), bStep.getState() == 2);
			}
		}

		for(int i = 8; i > 0; i--)
		{
			bStep.setStateUp(false);
			if(i > 10)
			{
				bBool2.setValue(false);
				CHECK_EQUAL(bBool2.getValue(), bStep.getState() == 2);
			}
			else
			{
				bBool1.setValue(false);
				CHECK_EQUAL(bBool1.getValue(), bStep.getState() == 1);
			}
		}
	}

	TEST(TestForceMax)
	{
		float upwardsThresholds[] = {0.7f, 1.7f};
		float downwardsThresholds[] = {0.3f, 1.3f};

		BufferedStep<3> bStep(0.0f, 2.0f, upwardsThresholds, downwardsThresholds, 0.1f);

		bStep.forceMax();

		CHECK_EQUAL(2u, bStep.getState());
	}

	TEST(TestForceMin)
	{
		float upwardsThresholds[] = {0.7f, 1.7f};
		float downwardsThresholds[] = {0.3f, 1.3f};

		BufferedStep<3> bStep(0.0f, 2.0f, upwardsThresholds, downwardsThresholds, 0.1f);

		for(int i = 0; i < 20; i++)
		{
			bStep.setStateUp(true);
		}

		bStep.forceMin();

		CHECK_EQUAL(0u, bStep.getState());
	}
}