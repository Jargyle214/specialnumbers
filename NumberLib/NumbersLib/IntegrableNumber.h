#ifndef _INTEGRABLE_NUMBER_H_
#define _INTEGRABLE_NUMBER_H_

#include "CyclicNumber.h"
#include "AbstractFilteredNumber.h"

namespace luma
{
namespace numbers
{
/**
	An integral number is a number that keeps track of itw own 
	integrals. 
	
	This class complements the DifferentiableNumber class.

	@param T
		The type that underlies this IntegrableNumber. Typically float.
	@param m
		The number of samples to store
	@param n
		The order of the integrable
*/
template <class T, unsigned int sampleCount, unsigned int maxOrder>
class IntegrableNumber: public AbstractFilteredNumber<T, sampleCount, maxOrder>
{
private:
	T mSamples[sampleCount];	
	float mTimeSamples[sampleCount];

	CyclicNumber<int> mCurrentIndex;	
	T mCurrentValue;
	T mInitialValue;

	IntegrableNumber<T, sampleCount, maxOrder - 1> mSum;
	float mTotalTime;

public:
	/**
		@param initialValue 
			zero of type T, returned by all calls 
			of getValue that this number cannot calculate.
	*/
	IntegrableNumber(T initialValue);

	/**
		Sets the value of this IntegrableNumber, and 
		recalculates all integrals.
	*/
	void setValue(T x, float elapsedTime = 1.0f);

	/**
	Forces this integrable number into a long term srteady state.
	The alpsed time is the time elapsed between samples. For example, 
	if this integrable number (with say, 10 samples) is forced to a 
	value of 10, with elapsed 
	time of 1.0f, then the sum would be 100. If the elapsed time is 3, 
	then the sum would be 300.
	*/
	void forceValue(T x, float elapsedTime = 1.0f);

	/**
		Returns the integral of 
		order specified for this IntegrableNumber.

		@param order
			-	if 0, the current value is returned
			-	if 1, the integral of the variable is returned
			-	if 2, the double integral of the value is returned
			-	if order > n, the initialValue (0) is returned.
	*/
	T getValue(int order) const;

	/**
		This returns the nth sample stored. Note that sample[0] 
		is not necesarily the oldest sample. This method is used 
		for testing, and should not be generally not be used in 
		production code. 
	*/
	T getSample(int i) const;
};

template <class T, unsigned int sampleCount, unsigned int maxOrder>
IntegrableNumber<T, sampleCount, maxOrder>::IntegrableNumber(T initialValue):
	mInitialValue(initialValue),
	mCurrentValue(initialValue),
	mCurrentIndex(0, 0, sampleCount, 1),
	mSum(initialValue),
	mTotalTime(sampleCount * TIME_UNIT)
{
	for(int i = 0; i < sampleCount; i++)
	{
		mSamples[i] = initialValue;
		mTimeSamples[i] = TIME_UNIT;
	}
}

template <class T, unsigned int sampleCount, unsigned int maxOrder>
void IntegrableNumber<T, sampleCount, maxOrder>::setValue(T x, float elapsedTime)
{
	T sum = mSum.getValue(0);

	mCurrentIndex++;

	int index = mCurrentIndex;
	T newValue = x * elapsedTime;

	mTotalTime += elapsedTime - mTimeSamples[index];
	sum += (newValue - mSamples[index]) / mTotalTime;	

	mSum.setValue(sum);	

	mSamples[index] = newValue;
	mCurrentValue = x;

}

template <class T, unsigned int sampleCount, unsigned int maxOrder>
void IntegrableNumber<T, sampleCount, maxOrder>::forceValue(T x, float elapsedTime)
{
	
	T newValue = x * elapsedTime;	// we do not have to multiply by the framerate
									// because we divide by the total time later

	T sum = mInitialValue;

	for(int i = 0; i < sampleCount; i++)
	{
		mSamples[i] = newValue;
		sum += newValue;
	}

	mTotalTime = sampleCount * elapsedTime;
	
	mSum.forceValue(sum / mTotalTime, elapsedTime);
	
	mCurrentValue = x;
}

template <class T, unsigned int sampleCount, unsigned int maxOrder>
T IntegrableNumber<T, sampleCount, maxOrder>::getValue(int order) const
{
	if(order == 0)
	{
		return mCurrentValue;
	}
	else if(order > 0)
	{
		if(order <= maxOrder)
		{
			return mSum.getValue(order - 1);
		}
	}

	return mInitialValue;

}

template <class T, unsigned int sampleCount, unsigned int maxOrder>
T IntegrableNumber<T, sampleCount, maxOrder>::getSample(int i) const
{
	return mSamples[i % sampleCount];
}

/**
	This is the stop class for the recursive template definition of
	IntegrableNumber. All the methods work the same as
	IntegrableNumber - see the documentation there.
*/
template <class T, unsigned int sampleCount>
class IntegrableNumber<T, sampleCount, 1>: public AbstractFilteredNumber<T, sampleCount, 1>
{
private:
	T mSamples[sampleCount];	
	T mTimeSamples[sampleCount];	
	CyclicNumber<int> mCurrentIndex;	
	T mCurrentValue;
	T mInitialValue;
	T mSum;
	float mTotalTime;

public:
	/**
		@see IntegrableNumber<T, sampleCount, n>::IntegrableNumber()
	*/
	IntegrableNumber(T initialValue);

	/**
		@see IntegrableNumber<T, sampleCount, n>::setValue()
	*/
	void setValue(T x, float elapsedTime = 1.0f);

	/**
		@see IntegrableNumber<T, sampleCount, n>::getValue()
	*/
	T getValue(int order) const;

	T getSample(int i) const;

	void forceValue(T x, float elapsedTime = 1.0f);
};

template <class T, unsigned int sampleCount>
IntegrableNumber<T, sampleCount, 1>::IntegrableNumber(T initialValue):
	mInitialValue(initialValue),
	mCurrentValue(initialValue),
	mCurrentIndex(0, 0, sampleCount, 1),
	mSum(initialValue),
	mTotalTime(sampleCount * TIME_UNIT)
{
	for(int i = 0; i < sampleCount; i++)
	{
		mSamples[i] = initialValue;
		mTimeSamples[i] = TIME_UNIT;
	}
}

template <class T, unsigned int sampleCount>
void IntegrableNumber<T, sampleCount, 1>::setValue(T x, float elapsedTime)
{
	mCurrentIndex++;

	int index = mCurrentIndex;

	T newValue = x * elapsedTime;

	mTotalTime += elapsedTime - mTimeSamples[index];
	mSum += (newValue - mSamples[index]) / mTotalTime;
	

	mSamples[index] = newValue;
	mTimeSamples[index] = elapsedTime;

	mCurrentValue = x;
}

template <class T, unsigned int sampleCount>
void IntegrableNumber<T, sampleCount, 1>::forceValue(T x, float elapsedTime)
{
	T newValue = x * elapsedTime;

	mSum = mInitialValue; //zero

	for(int i = 0; i < sampleCount; i++)
	{
		mSamples[i] = newValue;
		mTimeSamples[i] = elapsedTime;

		mSum += newValue;		
	}	

	mTotalTime = sampleCount * elapsedTime;
	mSum /= mTotalTime;


	mCurrentValue = x;
}

template <class T, unsigned int sampleCount>
T IntegrableNumber<T, sampleCount, 1>::getValue(int order) const
{
	if(order == 0)
	{
		return mCurrentValue;
	}
	else if(order == 1)
	{
		return mSum;
	}

	return mInitialValue;
}

template <class T, unsigned int sampleCount>
T IntegrableNumber<T, sampleCount, 1>::getSample(int i) const
{
	return mSamples[i % sampleCount];
}

/**
	This specialisation is provided for completeness' sake and should
	generally not be used. It is nothing more than a wrapper for the value;
	the elapsedTime is ignored.
*/
template <class T, unsigned int sampleCount>
class IntegrableNumber<T, sampleCount, 0>: public AbstractFilteredNumber<T, sampleCount, 0>
{
public:
	IntegrableNumber(T initialValue);
};

template <class T, unsigned int sampleCount>
IntegrableNumber<T, sampleCount, 0>::IntegrableNumber(T initialValue):
	AbstractFilteredNumber(initialValue)
{
}

}} //namespace

#endif //_INTEGRABLE_NUMBER_H_