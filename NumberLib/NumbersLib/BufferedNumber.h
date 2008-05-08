#ifndef _BUFFERED_NUMBER_H_
#define _BUFFERED_NUMBER_H_

#include "utils.h"
#include "ClampedNumber.h"
#include "UpdateableNumber.h"

namespace luma
{
namespace numbers
{

/**
	This class mimicks a float, but ensures smooth transitions. 
	The value returned grows towards the value set at a maximum 
	pace. 

	The function is updated everyTime setValue() is called.

	@f[
		y_n = y_{n-1} + \text{sign}(x_n - y_{n-1}) \max(d, |y_{n-1} - x_n|).
	@f]

	@author Herman Tulleken (herman.tulleken@gmail.com)
	
	The code of this documentation can be downloaded from
	http://www.luma.co.za/labs/2007/09/01/c-special-numbers-library/.
*/

template <class T, class Number = ClampedNumber<T>>
class BufferedNumber : public UpdateableNumber<T>
{
private:
	Number mIdealValue;
	Number mValue;

public:
	/**
		Constructs a new BufferedNumber. The number initial value
		is clamped between min and max.
	*/
	BufferedNumber(T initialValue, T min, T max, T increment);

	/**
		Returns the value of this buffered number. This value is
		always in the interval [min, max). 
	*/
	T getValue() const;

	/**
		Sets the next input sample for this BufferedNumber.
	*/
	void setValue(T value, float elapsedTime = TIME_UNIT);

	/**
		Forces the value of this BufferedNumber to the given value.
		After this funcion has been called, the value returned by 
		the next call to getValue will be the value passed to this 
		function.
	*/
	void forceValue(T value);
};

template <class T, class Number>
BufferedNumber<T, Number>::BufferedNumber(T initialValue, T min, T max, T increment):
	mIdealValue(initialValue, min, max, increment),
	mValue(initialValue, min, max, increment)
{
}

template <class T, class Number>
T BufferedNumber<T, Number>::getValue() const
{
	return mValue;
}

template <class T, class Number>
void BufferedNumber<T, Number>::setValue(T value, float elapsedTime)
{
	mIdealValue.setValue(value);

	if (mValue + mValue.increment() * elapsedTime * frameRate < mIdealValue)
		mValue.inc(elapsedTime);	
	else if(mValue - mValue.increment() * elapsedTime * frameRate > mIdealValue)
		mValue.dec(elapsedTime);
	else
		mValue.setValue(value);
}

template <class T, class Number>
void BufferedNumber<T, Number>::forceValue(T value)
{
	mIdealValue.setValue(value);
	mValue.setValue(value);
}

};}; //namespace

#endif //_BUFFERED_NUMBER_H_