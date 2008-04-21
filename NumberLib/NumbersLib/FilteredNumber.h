#ifndef _FILTERED_NUMBER_H_
#define _FILTERED_NUMBER_H_

#include "AbstractFilteredNumber.h"

/**
	A filtered number is a presentation of a 
	value as a weighted sum of past values. 
*/
template <class T, unsigned int sampleCount, unsigned int maxOrder>
class FilteredNumber : public AbstractFilteredNumber<T, sampleCount, maxOrder>
{
private:
	T mSamples[sampleCount];
	T mWeights[sampleCount];
	T mTimeSamples[sampleCount];
	T mInitialValue;
	T mCurrentValue;
	FilteredNumber<T, sampleCount, maxOrder - 1>mFilteredValue;
	CyclicNumber<int> mCurrentIndex;

public:
	/**
		Constructs a new filtered number. 
			@param initialValue 
				A zero of type T.
			@param weights
				The weights with which samples will be multiplied. 
				The size of the array must be sampleCount.
	*/
	FilteredNumber(T initialValue, T weights[]);

	/**
		Get the filtered value of the given order.
	*/
	T getValue(int order = 1) const;

	/**
		Sets the last sample for this filtered number. 
		This is the value returned by getValue(0) 
		(that is, when the order is 0).
	*/
	void setValue(T value, float elapsedTime=TIME_UNIT);

	/**
		Used for debugging and testing only!	
	*/
	T getSample(int i) const;

	/**
		Used for debugging and testing only!
	*/
	T getWeight(int i) const;
};

template <class T, unsigned int sampleCount, unsigned int maxOrder>
FilteredNumber<T, sampleCount, maxOrder>::FilteredNumber(T initialValue, T weights[]):
	mInitialValue(initialValue),
	mCurrentValue(initialValue),
	mFilteredValue(initialValue, weights),
	mCurrentIndex(0, 0, sampleCount, 1)
{

	for(int i = 0; i < sampleCount; i++)
	{
		mSamples[i] = initialValue;
		mWeights[i] = weights[i];		
		mTimeSamples[i] = TIME_UNIT;
	}
}

template <class T, unsigned int sampleCount, unsigned int maxOrder>
void FilteredNumber<T, sampleCount, maxOrder>::setValue(T value, float elapsedTime)
{
	mCurrentIndex++;

	int index = mCurrentIndex;
	T newValue = value * elapsedTime;

	mSamples[index] = newValue;
	mTimeSamples[index] = elapsedTime;
	mCurrentValue = value;

	T sum = mInitialValue;
	float totalTime = 0;

	for(int i = 0; i < sampleCount; i++)
	{
		sum += mSamples[(sampleCount + index - i) % sampleCount] * mWeights[i];
		totalTime += mTimeSamples[(sampleCount + index - i) % sampleCount] * mWeights[i];
	}

	mFilteredValue.setValue(sum / totalTime, elapsedTime);
}

template <class T, unsigned int sampleCount, unsigned int maxOrder>
T FilteredNumber<T, sampleCount, maxOrder>::getValue(int order) const
{
	if(order == 0)
	{
		return mCurrentValue;
	}
	else if (order > 0)
	{
		if(order <= maxOrder)
		{
			return mFilteredValue.getValue(order - 1);
		}
	}

	return mInitialValue;

}

template <class T, unsigned int sampleCount, unsigned int maxOrder>
T FilteredNumber<T, sampleCount, maxOrder>::getSample(int i) const
{
	return mSamples[i];
}

template <class T, unsigned int sampleCount, unsigned int maxOrder>
T FilteredNumber<T, sampleCount, maxOrder>::getWeight(int i) const
{
	return mWeights[i];
}

//order 1

template <class T, unsigned int sampleCount>
class FilteredNumber<T, sampleCount, 1> : public AbstractFilteredNumber<T, sampleCount, 1>
{
private:
	T mSamples[sampleCount];
	T mWeights[sampleCount];
	T mTimeSamples[sampleCount];
	T mInitialValue;
	T mCurrentValue;
	T mFilteredValue;

	CyclicNumber<int> mCurrentIndex;

public:
	FilteredNumber(T initialValue, T weights[]);
	T getValue(int order = 1) const;
	void setValue(T value, float elapsedTime=TIME_UNIT);

	T getSample(int i) const;
	T getWeight(int i) const;
};

template <class T, unsigned int sampleCount>
FilteredNumber<T, sampleCount, 1>::FilteredNumber(T initialValue, T weights[]):
	mInitialValue(initialValue),
	mCurrentValue(initialValue),
	mFilteredValue(initialValue),
	mCurrentIndex(0, 0, sampleCount, 1)
{
	for(int i = 0; i < sampleCount; i++)
	{
		mSamples[i] = initialValue;
		mWeights[i] = weights[i];
		mTimeSamples[i] = TIME_UNIT;
	}
}

template <class T, unsigned int sampleCount>
void FilteredNumber<T, sampleCount, 1>::setValue(T value, float elapsedTime)
{
	mCurrentIndex++;

	int index = mCurrentIndex;
	T newValue = value * elapsedTime;

	mSamples[index] = newValue;
	mTimeSamples[index] = elapsedTime;

	mCurrentValue = value;

	T sum = mInitialValue;
	float totalTime = 0;

	for(int i = 0; i < sampleCount; i++)
	{
		sum += mSamples[(sampleCount + index - i) % sampleCount] * mWeights[i];
		totalTime += mTimeSamples[(sampleCount + index - i) % sampleCount] * mWeights[i];
	}

	mFilteredValue = sum / totalTime;
}

template <class T, unsigned int sampleCount>
T FilteredNumber<T, sampleCount, 1>::getValue(int order) const
{
	if(order == 0)
	{
		return mCurrentValue;
	}
	else if(order == 1)
	{
		return mFilteredValue;
	}

	return mInitialValue;
}

template <class T, unsigned int sampleCount>
T FilteredNumber<T, sampleCount, 1>::getSample(int i) const
{
	return mSamples[i];
}

template <class T, unsigned int sampleCount>
T FilteredNumber<T, sampleCount, 1>::getWeight(int i) const
{
	return mWeights[i];
}

/**
	This implementation is provided for completeness sake, 
	and is merely a wrapper for the last sample passed to 
	setValue.
*/
template <class T, unsigned int sampleCount>
class FilteredNumber<T, sampleCount, 0>: public AbstractFilteredNumber<T, sampleCount, 0>
{
public:
	FilteredNumber(T initialValue, T weights[] = 0);
};

template <class T, unsigned int sampleCount>
FilteredNumber<T, sampleCount, 0>::FilteredNumber(T initialValue, T weights[]):
	AbstractFilteredNumber(initialValue)
{	
}


#endif //_FILTERED_NUMBER_H_