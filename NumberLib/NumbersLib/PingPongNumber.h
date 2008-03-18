#ifndef _PING_PONG_NUMBER_H
#define _PING_PONG_NUMBER_H

#include "RangedNumber.h"
#include "CyclicNumber.h"

namespace luma
{
namespace numbers
{

/**
	A PingPongNumber is a number that can grow (or shrink) up to a point, 
	and then starts shrinking (or growing) again.

	@author Herman Tulleken (herman@luma.co.za)
	@author luma/games (http://www.luma.co.za/)

	For example:

	@code

	PingPongNumber n(0, 0, 3, 1);

	for(int i = 0; i < 7; i++)
	{
		n++;
		cout << n << " ";
	}
	@endcode

	will print 0 1 2 1 0 1 2.

	@param T
		Must be 
*/
template <class T>
class PingPongNumber: public RangedNumber<T>
{
private:
	CyclicNumber<T> mCyclicNumber;

	/**
		Converts the internal cyclic value to a ping pong value.
	*/
	inline T pingPongValue(T value)
	{
		return value > mMax ? mCyclicNumber.max() - value: value;
	}

	/**
		Converts the internal cyclic value to a ping pong value.
	*/
	inline T pingPongValue()
	{
		return pingPongValue((T) mCyclicNumber);
	}

public:
	/**
		Constructs a new PingPongNumber with the given 
		value, min, max, and direction.
	*/
	PingPongNumber(T value, T min, T max, T increment);

	/**

	*/
	PingPongNumber(const PingPongNumber& other);

	PingPongNumber<T>& operator=(const PingPongNumber<T>& other);
	PingPongNumber<T>& operator=(const T& value);

	PingPongNumber<T>& operator++();
	PingPongNumber<T> operator++(int);
	PingPongNumber<T>& operator--();
	PingPongNumber<T> operator--(int);

	virtual void dec(float elapsedTime = 1);
	virtual void inc(float elapsedTime = 1);

	virtual T getValidValue(const T& value);
};

template <class T>
PingPongNumber<T>::PingPongNumber(T value, T min, T max, T increment):
	RangedNumber(reflect(value, min, max - increment), min, max, increment),
	mCyclicNumber(value, min, max + max - min + increment, increment)
{
}

template <class T>
PingPongNumber<T>::PingPongNumber(const PingPongNumber &other):
	RangedNumber(other),
	mCyclicNumber(other.mCyclicNumber)
{
}

template <class T>
PingPongNumber<T>& PingPongNumber<T>::operator=(const PingPongNumber<T>& other)
{
	modify(other.mMin, other.mMax, other.mIncrement);
	mCyclicNumber = other.mCyclicNumber;
	mValue = pingPongValue();

	return *this;
}

template <class T>
PingPongNumber<T>& PingPongNumber<T>::operator=(const T& value)
{
	mCyclicNumber = value;
	mValue = pingPongValue();

	return *this;
}

template <class T>
PingPongNumber<T>& PingPongNumber<T>::operator++()
{
	inc();

	return *this;
}

template <class T>
PingPongNumber<T> PingPongNumber<T>::operator++(int)
{
	PingPongNumber<T> tmp = *this;

	++*this;

	return tmp;
}

template <class T>
PingPongNumber<T>& PingPongNumber<T>::operator--()
{
	dec();

	return *this;
}

template <class T>
PingPongNumber<T> PingPongNumber<T>::operator--(int)
{
	PingPongNumber<T> tmp = *this;

	--*this;

	return tmp;
}

template <class T>
T PingPongNumber<T>::getValidValue(const T& value)
{
	return pingPongValue(mCyclicNumber.getValidValue(value));
}

template <class T>
void PingPongNumber<T>::inc(float ellapsedTime)
{
	mCyclicNumber.inc(ellapsedTime);
	mValue = pingPongValue((T) mCyclicNumber);

}

template <class T>
void PingPongNumber<T>::dec(float ellapsedTime)
{
	mCyclicNumber.dec(ellapsedTime);
	mValue = pingPongValue((T) mCyclicNumber);

}

};};//namespace
#endif //_PING_PONG_NUMBER_H