#ifndef _CYCLIC_NUMBER_H
#define _CYCLIC_NUMBER_H

#include "utils.h"
#include "RangedNumber.h"

namespace luma
{
namespace numbers
{

/**
	A cyclic number is a number that is always in a given range, and wraps 
	around when it would exceed this range.

	For example, 

	@code
	CyclicNumber<int> c(0, 0, 4, 1);

	c += 10;
	cout << c;
	@endcode

	prints 2.

*/
template <class T>
class CyclicNumber: public RangedNumber<T>
{

public:
	CyclicNumber(T value, T min, T max, T increment);


	CyclicNumber<T>& operator=(const CyclicNumber<T>& other);
	CyclicNumber<T>& operator=(const T& value);
	/**
		Pre-increments this Cyclic number's value with 
		increment, and wraps it around if it exceeds the 
		max.
	*/
	CyclicNumber<T>& operator++();
	
	/**
		Post-increments this Cyclic number's value with 
		increment, and wraps it around if it exceeds the 
		max.
	*/
	CyclicNumber<T> operator++(int);

	/**
		Pre-decrements this Cyclic number's value with 
		increment, and wraps it around if it exceeds the 
		max.
	*/
	CyclicNumber<T>& operator--();

	/**
		Post-decrements this Cyclic number's value with 
		increment, and wraps it around if it exceeds the 
		max.
	*/
	CyclicNumber<T> operator--(int);

	/**
		Increments this CyclicNumber's value by the
		given increment, and waps it around.
	*/
	CyclicNumber<T>& operator+=(const T& increment);

	/**
		Decrements this CyclicNumber's value by the
		given increment, and waps it around.
	*/
	CyclicNumber<T>& operator-=(const T& decrement);

	virtual T getValidValue(const T& value);

	virtual void dec(float elapsedTime = 1);
	virtual void inc(float elapsedTime = 1);
};

template <class T>
CyclicNumber<T>::CyclicNumber(T value, T min, T max, T increment):
	RangedNumber(mod(value, min, max), min, max, increment)
{
}

template <class T>
CyclicNumber<T>& CyclicNumber<T>::operator=(const CyclicNumber<T>& other)
{
	this->RangedNumber::operator=(other);
	/*
	mValue = mod((T) other, mMin, mMax);
	*/
	return *this;
}

template <class T>
CyclicNumber<T>& CyclicNumber<T>::operator=(const T& value)
{
	mValue = mod((T) value, mMin, mMax);

	return *this;
}

template <class T>
CyclicNumber<T>& CyclicNumber<T>::operator++()
{
	inc();

	return *this;
}

template <class T>
CyclicNumber<T> CyclicNumber<T>::operator++(int)
{
	CyclicNumber<T> tmp = *this;
	++*this;

	return tmp;
}

template <class T>
CyclicNumber<T>& CyclicNumber<T>::operator--()
{
	dec();

	return *this;
}

template <class T>
CyclicNumber<T> CyclicNumber<T>::operator--(int)
{
	CyclicNumber<T> tmp = *this;
	--*this;

	return tmp;
}

template <class T>
CyclicNumber<T>& CyclicNumber<T>::operator+=(const T& increment)
{
	mValue += increment;
	mValue = mod(mValue, mMin, mMax);

	return *this;
}

template <class T>
CyclicNumber<T>& CyclicNumber<T>::operator-=(const T& increment)
{
	mValue -= increment;
	mValue = mod(mValue, mMin, mMax);

	return *this;
}

template <class T>
T CyclicNumber<T>::getValidValue(const T& value)
{
	return mod(value, mMin, mMax);
}

template <class T>
void CyclicNumber<T>::inc(float ellapsedTime)
{
	mValue += (T)(mIncrement * ellapsedTime);
	mValue = mod(mValue, mMin, mMax);
}

template <class T>
void CyclicNumber<T>::dec(float ellapsedTime)
{
	mValue -= (T) (mIncrement * ellapsedTime);
	mValue = mod(mValue, mMin, mMax);
}

}} //namespace
#endif //_CYCLIC_NUMBER_H