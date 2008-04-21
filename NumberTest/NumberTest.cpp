/**
	RangedNumber cannot be tested directly. ClampedNumber is used to test many of
	RangedNumber's methods. See TestClampedNumber for an exaplanation.
*/

#include "UnitTest++.h"

#include "TestUtils.h"

#include "TestNumberWrapper.h"

#include "TestClampedNumber.h"
#include "TestCyclicNumber.h"
#include "TestPingPongNumber.h"

#include "TestBufferedBool.h"
#include "TestBufferedState.h"
#include "TestBufferedStep.h"

#include "TestResponseCurve.h"
#include "TestBufferedNumber.h"

#include "TestFilteredNumber.h"

#include "TestDifferentiableNumber.h"
#include "TestIntegrableNumber.h"
#include "TestPIDBufferedNumber.h"

#include "TestPeriodicResponseCurve.h"

#include "BufferedNumber.h"

#include <stdlib.h>

int main(int , char * [])
{
	return UnitTest::RunAllTests();
}

