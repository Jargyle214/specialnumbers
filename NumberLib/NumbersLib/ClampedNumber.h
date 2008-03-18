#ifndef _CLAMPED_NUMBER_H
#define _CLAMPED_NUMBER_H

#include "utils.h"
#include "RangedNumber.h"

namespace luma
{

namespace numbers
{

/**
	Class that represents a number that is always clamped in a range.

	@param T
		It is unsafe to use this class with a number type whose min or max
		coincides with the ClampedNumber's min or max. For instance, do not
		use unsigned int if the range is between 0 and some positive number.

	@todo Make it possible to use with unsigned int and 0 as bottom limit.

	@author Herman Tulleken (herman@luma.co.za)
	@author luma/games (http://www.luma.co.za/)
*/
template <class T>
class ClampedNumber: public RangedNumber<T>
{
protected:
	virtual T getValidValue(const T& value);
public:
	/**
		Creates a ClampedNumber clamped between min and max - increment, with the given value.
		The given vale is also clamped.
	*/
	ClampedNumber(T value, T min, T max, T increment);

	/**
		Copies all attributes of the other clmaped number to this
		ClampedNumber.
	*/
	ClampedNumber(const ClampedNumber<T>& other);

	/**
		Returns this ClampedNumber's value.
	*/
	//ClampedNumber& operator=(T value);

	/**
		Sets the value of this ClampedNumber to the value of
		the other value, and clamps it within this ClampedNumber's
		range. This ClampedNumber's range is not changed.
	*/
	ClampedNumber& operator=(const ClampedNumber<T>& other);

	/**
		Increments this CyclicNumber's value by the
		given increment, and waps it around.
	*/
	ClampedNumber<T>& operator+=(const T& increment);

	/**
		Decrements this CyclicNumber's value by the
		given increment, and waps it around.
	*/
	ClampedNumber<T>& operator-=(const T& decrement);

	virtual ClampedNumber<T>& operator++();
	virtual ClampedNumber<T> operator++(int);
	virtual ClampedNumber<T>& operator--();
	virtual ClampedNumber<T> operator--(int);
	virtual void dec(float elapsedTime = 1);
	virtual void inc(float elapsedTime = 1);
};

template <class T>
ClampedNumber<T>::ClampedNumber(T value, T min, T max,T increment):
	RangedNumber<T>(clamp(value, min, max - increment), min, max, increment)
{
}

template <class T>
ClampedNumber<T>::ClampedNumber(const ClampedNumber<T>& other):
	RangedNumber<T>(other)
{}

/*template <class T>
ClampedNumber<T>& ClampedNumber<T>::operator=(T value)
{
	mValue = getValidValue(value);
	return *this;
}*/

template <class T>
ClampedNumber<T>& ClampedNumber<T>::operator=(const ClampedNumber<T>& other)
{
	return dynamic_cast<ClampedNumber<T>&>(RangedNumber<T>::operator=(other));
}

template <class T>
ClampedNumber<T>& ClampedNumber<T>::operator++()
{
	RangedNumber<T>::mValue += RangedNumber<T>::mIncrement;
	RangedNumber<T>::mValue = clamp(RangedNumber<T>::mValue, RangedNumber<T>::mMin, RangedNumber<T>::mMax - RangedNumber<T>::mIncrement);

	return *this;
}

template <class T>
ClampedNumber<T> ClampedNumber<T>::operator++(int)
{
	ClampedNumber<T> tmp = *this;
	++*this;

	return tmp;
}

template <class T>
ClampedNumber<T>& ClampedNumber<T>::operator--()
{
	RangedNumber<T>::mValue -= RangedNumber<T>::mIncrement;
	RangedNumber<T>::mValue = clamp(RangedNumber<T>::mValue, RangedNumber<T>::mMin, RangedNumber<T>::mMax - RangedNumber<T>::mIncrement);

	return *this;
}

template <class T>
ClampedNumber<T> ClampedNumber<T>::operator--(int)
{
	ClampedNumber<T> tmp = *this;
	--*this;

	return tmp;
}

template <class T>
ClampedNumber<T>& ClampedNumber<T>::operator+=(const T& increment)
{
	RangedNumber<T>::mValue += RangedNumber<T>::increment;
	RangedNumber<T>::mValue = clamp(RangedNumber<T>::mValue, RangedNumber<T>::mMin, RangedNumber<T>::mMax - RangedNumber<T>::increment);

	return *this;
}

template <class T>
ClampedNumber<T>& ClampedNumber<T>::operator-=(const T& increment)
{
	RangedNumber<T>::mValue -= RangedNumber<T>::increment;
	RangedNumber<T>::mValue = clamp(RangedNumber<T>::mValue, RangedNumber<T>::mMin, RangedNumber<T>::mMax - RangedNumber<T>::increment);

	return *this;
}

template <class T>
T ClampedNumber<T>::getValidValue(const T& value)
{
	return clamp(value, RangedNumber<T>::mMin, RangedNumber<T>::mMax - RangedNumber<T>::mIncrement);
}

template <class T>
void ClampedNumber<T>::inc(float ellapsedTime)
{
	RangedNumber<T>::mValue += (T)(RangedNumber<T>::mIncrement * ellapsedTime * frameRate);
	RangedNumber<T>::mValue = clamp(RangedNumber<T>::mValue, RangedNumber<T>::mMin, RangedNumber<T>::mMax - RangedNumber<T>::mIncrement);
}

template <class T>
void ClampedNumber<T>::dec(float ellapsedTime)
{
	RangedNumber<T>::mValue -= (T)(RangedNumber<T>::mIncrement * ellapsedTime * frameRate);
	RangedNumber<T>::mValue = clamp(RangedNumber<T>::mValue, RangedNumber<T>::mMin, RangedNumber<T>::mMax - RangedNumber<T>::mIncrement);
}

}}//namespace
#endif //_CLAMPED_NUMBER_H
