#ifndef _RANGED_NUMBER_H
#define _RANGED_NUMBER_H

#include "numbers.h"

namespace luma
{
namespace numbers
{

/**
	This class is the base class of numbers that fall
	in a given range.

	@author Herman Tulleken (herman@luma.co.za)
	@author luma/games (http://www.luma.co.za/)

	The derrived classes differ	by how out of range situations
	are handled. For example, the ClampedNumber class clamps its
	values in range, and CyclicNumber cycles it values in range.

	A class derrived from this type must guarentee that
	the value (as returned by the cast operator) is always
	in the half-open range [min, max).

	@param T
		T must be a class that supports default construction,
		and have the stream operator class overloaded. Base
		classes might specify further requirements.
*/
template <class T>
class RangedNumber
{
protected:
    T mValue;
	T mMin;
	T mMax;
	T mIncrement;

public:
	/**
		Constructs a new RangedNumber.

		@param value
			The current value of this RangedNumber. The value must
			lie in the range [min, max).

		@param min
			The minimum value of this RangedNumber (inclusive).

		@param max
			The maximum value of this RangedNumber (exclusive).

		@param increment
			This is the value used by operator++() and operator--().
			In general, this value is such that this RangeNumber's
			value is always between [min, max - increment].
	*/
	RangedNumber(T value, T min, T max, T increment);

	virtual RangedNumber& operator=(const RangedNumber<T>&);
	virtual RangedNumber& operator=(const T&);
	void setIncrement(const T&);
	void setValue(const T& value) { mValue = getValidValue(value);}
	
	/**
		Changes the way this RangedNumber works.
	*/
	void modify(const T& max, const T& min, const T& increment);

	/**
	*/
	RangedNumber(const RangedNumber& other);


	/**
		A virtual destructor is provided so that
		sub classes can properly be destructed.
	*/
	virtual ~RangedNumber(){};

	/**
		Returns this ClampedNumber's value.
	*/
	virtual operator T() const;

	/**
		Puts this ClampedNumber's value onto the stream.
	*/
	/*friend ostream& operator<<(ostream& os, const RangedNumber<T>& num)
	{
		os << num.mValue;
		return os;
	}*/

	/**
		Increments this RangedNumber by one increment, as specified by
		the constructor.
	*/
	virtual RangedNumber<T>& operator++() = 0;
	//virtual RangedNumber<T> operator++(int);

	/**
		Decrements this RangedNumber by one increment, as specified by
		the constructor.
	*/
	virtual RangedNumber<T>& operator--() = 0;
	//virtual RangedNumber<T> operator--(int);

	virtual void inc(float elapsedTime = 1) = 0;
	virtual void dec(float elapsedTime = 1) = 0;

	/**
		Returns the min value of this RangedNumber.
	*/
	const T& min() const;

	/**
		Returns the max value of this RangedNumber.
	*/
	const T& max() const;

	/**
		Returns the increment for this RangedNumber.
	*/
	const T& increment() const;

	virtual T getValidValue(const T& value) const = 0;

	/**
		Returns the vlaue of this ranged number.
	*/
	T getValue() const;
};



template <class T>
RangedNumber<T>::RangedNumber(T value, T min, T max, T increment):
	mValue(value),
	mMin(min),
	mMax(max),
	mIncrement(increment)	
{
}

template <class T>
RangedNumber<T>::RangedNumber(const RangedNumber& other):
	mValue(other.mValue),
	mMin(other.mMin),
	mMax(other.mMax),
	mIncrement(other.mIncrement)
{
}

template <class T>
RangedNumber<T>& RangedNumber<T>::operator=(const RangedNumber<T>& other)
{
	modify(other.mMin, other.mMax, other.mIncrement);
	mValue = getValidValue(other.mValue);

	return *this;
}

template <class T>
RangedNumber<T>& RangedNumber<T>::operator=(const T& value)
{
	mValue = getValidValue(value);

	return *this;
}

template <class T>
const T& RangedNumber<T>::min() const
{
	return mMin;
}

template <class T>
const T& RangedNumber<T>::max() const
{
	return mMax;
}

template <class T>
const T& RangedNumber<T>::increment() const
{
	return mIncrement;
}

template <class T>
RangedNumber<T>::operator T() const
{
	return mValue;
}

template <class T>
void RangedNumber<T>::modify(const T& min, const T& max, const T& increment)
{
	mMin = min;
	mMax = max;
	mIncrement = increment;

	mValue = getValidValue(mValue);
}

template <class T>
void RangedNumber<T>::setIncrement(const T& increment)
{
	mIncrement = increment;
	mValue = getValidValue(mValue);
}

template <class T>
T RangedNumber<T>::getValue() const
{
	return mValue;
}

}} //namespace
#endif
