#ifndef _NUMBER_WRAPPER_H_
#define _NUMBER_WRAPPER_H_

namespace luma{
namespace numbers {


/**
	This class is a drop-in substitute for 
	RangedNumbers, except that it has no 
	logic wrapped around it's value - that 
	is, gertValue will always returned the 
	last value passed to setValue.

	This class is useful for debugging purposes
	(for example, testing something without 
	filtering), and should not be used in production 
	code. 
	
	It might be removed in the future.
*/
template <class T>
class NumberWrapper
{
public:

	/** 
		Constructs a new NumberWrapper with the given initial value.
	*/
	NumberWrapper(T value);

	/** 
		Constructs a new NumberWrapper with the given initial value. 
		Other parameters are ignored.
	*/
	NumberWrapper(T value, T min, T max, T increment);

	/**
		Sets the value of this NumberWrapper to the given value.
		The elapsedTime parameter is ignored.
	*/
	void setValue(T value, float elapsedTime = 1.0f);

	/**
		Returns the value of this NumberWrapper, that is either the 
		last value passed to setValue, or if it has not been called, 
		the value passed to the constructor.
	*/
	T getValue() const;

private:
	T mValue;
};

template <class T>
NumberWrapper<T>::NumberWrapper(T value):
	mValue(value)
{
}

template <class T>
NumberWrapper<T>::NumberWrapper(T value, T, T, T):
	mValue(value)
{
}

template <class T>
void NumberWrapper<T>::setValue(T value, float)
{
	mValue = value;
}

template <class T>
T NumberWrapper<T>::getValue() const
{
	return mValue;
}

}}



#endif _NUMBER_WRAPPER_H_