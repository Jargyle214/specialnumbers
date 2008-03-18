#ifndef _BUFFERED_STEP_H
#define _BUFFERED_STEP_H

#include "ClampedNumber.h"
namespace luma
{
namespace numbers
{

/**
	This class combines ideas from BufferedBool and BufferedState; 
	it represents a linear progression of buffered states. States
	are represented by integers in the range 0..n-1.

	It is easier to predict the behaviour for this class if there 
	exists a number k such that 
	
	@code
	0 < l_0 < h_0 < k < l_1 < h_1 < ... < l_i < h_i < i*k < ... < (n - 1)*k
	@endcode

	is true. In this case, the states resemebles a chained sequence of BufferedBool instances, 
	where each true state of one is associated with a 

	@param n 
		must be greater than 1, the number states.
*/
template <unsigned int n> 
class BufferedStep
{
private:
	float mUpwardsThresholds[n - 1];
	float mDownwardsThresholds[n - 1];
	ClampedNumber<int> mState;
	ClampedNumber<float> mFloatValue;

	int static indexFromState(int n) { return n > 1 ? n - 1 : 0;};

public:
	BufferedStep(float mMin, float mMax, float upwardsThresholds[n - 1], float downwardsThresholds[n - 1], float interval);
	unsigned int getState() const;
	void setStateUp(bool up);
	void forceMin();
	void forceMax();

};

template <unsigned int n>
BufferedStep<n>::BufferedStep(float min, float max, float upwardsThresholds[n - 1], float downwardsThresholds[n - 1], float interval):
	mFloatValue(min, min, max, interval),
	mState(0, 0, n, 1)
{
	for(int i = 0; i < n - 1; i++)
	{
		mUpwardsThresholds[i] = upwardsThresholds[i];
		mDownwardsThresholds[i] = downwardsThresholds[i];
	}
}

template <unsigned int n>
unsigned int BufferedStep<n>::getState() const
{
	return mState;
}

template <unsigned int n>
void BufferedStep<n>::setStateUp(bool up)
{
	if(up)
	{
		mFloatValue++;
		
		if((float) mFloatValue > mUpwardsThresholds[mState.operator int()])
		{
			mState++;
		}
	}
	else
	{
		mFloatValue--;

		if((float) mFloatValue < mDownwardsThresholds[indexFromState(mState)])
		{
			mState--;
		}
	}
}

template <unsigned int n>
void BufferedStep<n>::forceMin()
{
	mFloatValue.setValue(mFloatValue.min());
	mState.setValue(0);
}

template <unsigned int n>
void BufferedStep<n>::forceMax()
{
	mFloatValue.setValue(mFloatValue.max());
	mState.setValue(n - 1);
}

};}; //namespace
#endif//_BUFFERED_STEP_H