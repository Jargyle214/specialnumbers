#ifndef _ABSTRACT_FILTERED_NUMBER_H_
#define _ABSTRACT_FILTERED_NUMBER_H_

/**
	
*/
template <class T, unsigned int sampleCount, unsigned int maxOrder>
class AbstractFilteredNumber
{

public:
	/**
		Get the current value of this AbstractFilteredNumber of the given order.

	*/
	virtual T getValue(int order = 1) const = 0;
	virtual void setValue(T value, float elapsedTime=TIME_UNIT) = 0;
};

/**
	This specialisation is provided for completeness' sake and should
	generally not be used. It is nothing more than a wrapper for the value;
	the elapsedTime is ignored.
*/
template <class T, unsigned int sampleCount>
class AbstractFilteredNumber<T, sampleCount, 0>
{
private:
	T mCurrentValue;
	T mInitialValue;


public:
	AbstractFilteredNumber(T initialValue);

	/**
		Sets the current value of this AbstractFilteredNumber.
		The elapsedTime variable is ignored.
	*/
	virtual void setValue(T x, float elapsedTime = 1.0f);

	/**
		Only m = 0 will give anything other than the 
		initialValue.
	*/
	virtual T getValue(int order) const;

	/** 
		The elapsed time is ignored.
	*/
	virtual void forceValue(T x, float elapsedTime = 1.0f);
};

template <class T, unsigned int sampleCount>
AbstractFilteredNumber<T, sampleCount, 0>::AbstractFilteredNumber(T initialValue):
	mInitialValue(initialValue),
	mCurrentValue(initialValue)
{
}

template <class T, unsigned int sampleCount>
void AbstractFilteredNumber<T, sampleCount, 0>::setValue(T x, float /*ignore parameter*/)
{
	mCurrentValue = x;
}

template <class T, unsigned int sampleCount>
void AbstractFilteredNumber<T, sampleCount, 0>::forceValue(T x, float /*ignore parameter*/)
{
	mCurrentValue = x;
}

template <class T, unsigned int sampleCount>
T AbstractFilteredNumber<T, sampleCount, 0>::getValue(int order) const
{
	if(order == 0)
	{
		return mCurrentValue;
	}
	
	return mInitialValue;
}

#endif //_ABSTRACT_FILTERED_NUMBER_H_