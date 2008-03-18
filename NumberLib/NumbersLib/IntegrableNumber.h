#ifndef _INTEGRABLE_NUMBER_H_
#define _INTEGRABLE_NUMBER_H_

#include "CyclicNumber.h"

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
template <class T, unsigned int m, unsigned int n>
class IntegrableNumber
{
private:
	T mSamples[m];	
	CyclicNumber<int> mCurrentIndex;	
	T mCurrentValue;
	T mInitialValue;
	IntegrableNumber<T, m, n - 1> mSum;

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
		Returns the integral of 
		order specified for this IntegrableNumber.

		@param order
			-	if 0, the current value is returned
			-	if 1, the integral of the variable is returned
			-	if 2, the double integral of the value is returned
			-	if order > n, the initialValue (0) is returned.
	*/
	T getValue(int order);
};

template <class T, unsigned int m, unsigned int n>
IntegrableNumber<T, m, n>::IntegrableNumber(T initialValue):
	mInitialValue(initialValue),
	mCurrentValue(initialValue),
	mCurrentIndex(0, 0, m, 1),
	mSum(initialValue)
{
	for(int i = 0; i < m; i++)
	{
		mSamples[i] = initialValue;
	}
}

template <class T, unsigned int m, unsigned int n>
void IntegrableNumber<T, m, n>::setValue(T x, float elapsedTime)
{
	T sum = mSum.getValue(0);

	mCurrentIndex++;

	int index = mCurrentIndex;

	T newValue = x * elapsedTime * frameRate;

	sum += newValue - mSamples[index];

	mSum.setValue(sum);

	mSamples[index] = newValue;
	mCurrentValue = x;

}

template <class T, unsigned int m, unsigned int n>
T IntegrableNumber<T, m, n>::getValue(int order)
{
	if(order == 0)
	{
		return mCurrentValue;
	}
	else if(order > 0)
	{
		if(order <= n)
		{
			return mSum.getValue(order - 1);
		}
	}

	return mInitialValue;

}

/**
	This is the stop class for the recursive template definition of
	IntegrableNumber. All the methods work the same as
	IntegrableNumber - see the documentation there.
*/
template <class T, unsigned int m>
class IntegrableNumber<T, m, 1>
{
private:
	T mSamples[m];	
	CyclicNumber<int> mCurrentIndex;	
	T mCurrentValue;
	T mInitialValue;
	T mSum;

public:
	/**
		@see IntegrableNumber<T, m, n>::IntegrableNumber()
	*/
	IntegrableNumber(T initialValue);

	/**
		@see IntegrableNumber<T, m, n>::setValue()
	*/
	void setValue(T x, float elapsedTime = 1.0f);

	/**
		@see IntegrableNumber<T, m, n>::getValue()
	*/
	T getValue(int order);
};

template <class T, unsigned int m>
IntegrableNumber<T, m, 1>::IntegrableNumber(T initialValue):
	mInitialValue(initialValue),
	mCurrentValue(initialValue),
	mCurrentIndex(0, 0, m, 1),
	mSum(initialValue)
{
	for(int i = 0; i < m; i++)
	{
		mSamples[i] = initialValue;
	}
}

template <class T, unsigned int m>
void IntegrableNumber<T, m, 1>::setValue(T x, float elapsedTime)
{
	mCurrentIndex++;

	int index = mCurrentIndex;

	T newValue = x * elapsedTime * frameRate;

	mSum += newValue - mSamples[index];
	mSamples[index] = newValue;
	mCurrentValue = x;
}

template <class T, unsigned int m>
T IntegrableNumber<T, m, 1>::getValue(int order)
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

/**
	This specialisation is provided for completeness' sake and should
	generally not be used. It is nothing more than a wrapper for the value;
	the elapsedTime is ignored.
*/
template <class T, unsigned int m>
class IntegrableNumber<T, m, 0>
{
private:
	T mCurrentValue;
	T mInitialValue;


public:
	IntegrableNumber(T initialValue);

	/**
		Sets the current value of this IntegrableNumber.
		The elapsedTime variable is ignored.
	*/
	void setValue(T x, float elapsedTime = 1.0f);

	/**
		Only m = 0 will give anything other than the 
		initialValue.
	*/
	T getValue(int order);
};

template <class T, unsigned int m>
IntegrableNumber<T, m, 0>::IntegrableNumber(T initialValue):
	mInitialValue(initialValue),
	mCurrentValue(initialValue)
{
}

template <class T, unsigned int m>
void IntegrableNumber<T, m, 0>::setValue(T x, float elapsedTime)
{
	mCurrentValue = x;
}

template <class T, unsigned int m>
T IntegrableNumber<T, m, 0>::getValue(int order)
{
	if(order == 0)
	{
		return mCurrentValue;
	}
	
	return mInitialValue;
}

}} //namespace

#endif //_INTEGRABLE_NUMBER_H_