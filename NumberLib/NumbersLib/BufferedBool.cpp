#include "BufferedBool.h"

namespace luma
{
namespace numbers
{

BufferedBool::BufferedBool(float bottomThreshold, float topThreshold, float increment):
	mBottomThreshold(bottomThreshold),
	mTopThreshold(topThreshold),
	mFloatValue(0.0f, 0.0f, 1.0f, increment),
	mBoolValue(false)
{
}

void BufferedBool::setValue(bool value, float ellapsedTime)
{
	if(value)
	{
		mFloatValue.inc(ellapsedTime);

		//above threshold - so switch
		if(mFloatValue > mTopThreshold)
		{
			mBoolValue = true;
		}
	}
	else
	{
		mFloatValue.dec(ellapsedTime);

		//below threshold - so swith
		if(mFloatValue < mBottomThreshold)
		{
			mBoolValue = false;
		}
	}
}

bool BufferedBool::getValue() const
{
	return mBoolValue;
}

void BufferedBool::forceValue(bool value)
{
	mBoolValue = value;
	mFloatValue.setValue(value ? mFloatValue.max() : mFloatValue.min());
}

void BufferedBool::setIncrement(float increment)
{
	mFloatValue.setIncrement(increment);
}

float BufferedBool::getFloatValue() const
{
	return mFloatValue.getValue();
}

}} //namespace
