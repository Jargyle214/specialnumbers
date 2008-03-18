#ifndef _BUFFERED_NUMBER_H_
#define _BUFFERED_NUMBER_H_

#include "utils.h"
#include "ClampedNumber.h"

namespace luma
{
namespace numbers
{

/**
	This class mimicks a float, but ensures smooth transitions. 
	The value returned grows towards the value set. 

	The function is updated everyTime setValue() is called.

	@author Herman Tulleken (herman@luma.co.za)
	@author luma/games (http://www.luma.co.za/)

	The code of this documentation can be downloaded from
	http://www.luma.co.za/labs/2007/09/01/c-special-numbers-library/.
*/

template <class T, class Number = ClampedNumber<T>>
class BufferedNumber
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
	T getValue();
	void setValue(T value, float elapsedTime = 1.0f);
};

template <class T, class Number>
BufferedNumber<T, Number>::BufferedNumber(T initialValue, T min, T max, T increment):
	mIdealValue(initialValue, min, max, increment),
	mValue(initialValue, min, max, increment)
{
}

template <class T, class Number>
T BufferedNumber<T, Number>::getValue()
{
	return mValue;
}

template <class T, class Number>
void BufferedNumber<T, Number>::setValue(T value, float elapsedTime)
{
	mIdealValue.setValue(value);

	if(mValue < mIdealValue)
		mValue.inc(elapsedTime);	
	else if(mValue > mIdealValue)
		mValue.dec(elapsedTime);
}

};}; //namespace

#endif //_BUFFERED_NUMBER_H_