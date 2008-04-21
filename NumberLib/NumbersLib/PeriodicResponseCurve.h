#ifndef _PERIODIC_RESPONSE_CURVE_H_
#define _PERIODIC_RESPONSE_CURVE_H_

#include "ResponseCurve.h"
#include "Utils.h"

/**
	This class is useful for implementing arbitrary periodic functions. 
	It works exactly like ResponseCurve, except that the input is wrapped 
	so that it is always between the inputMin and the inputMax. Note that
	the value returned for inputMax is the same as the output at inputMin.

*/
template <class T, unsigned int n>
class PeriodicResponseCurve
{
public:
	/**
		Constructs a new Periodic response curve.
		
		@param inputMin
			The minimum value an input can be. 
		@param inputMax
			The maximum value an input can be.
		@param outputSamples
			Samples of outputs.
	*/
	PeriodicResponseCurve(T inputMin, T inputMax, T outputSamples[n]);


	/**
		A new inputValue is calculated so that 

		@code
			newInputValue = (inPutValue) + m * (inputMax - inputMin)
		@endcode

		for some integer m such that 
		
		@code
			inputMin < newInputValue < inputMax
		@endcode
		
		Then an index is calculated for this input value, and the output is 
		interpolated between outputSample[index] and outputSample[index + 1].

		@param input
			The input for which output is sought.
	*/
	T operator()(const T input) const;

	/**
		Returns the inputMin for this PeriodicResponseCurve
		(the value pass to the constructor).
	*/
	inline T getInputMin() const;

	/**
		Returns the outputMin for this PeriodicResponseCurve 
		(the value passed to the constructor).
	*/
	inline T getInputMax() const;

private:	
	ResponseCurve<T, n> mResponseCurve;

};

template <class T, unsigned int n>
PeriodicResponseCurve<T, n>::PeriodicResponseCurve(T inputMin, T inputMax, T outputSamples[n]):
	mResponseCurve(inputMin, inputMax, outputSamples)
{}

template <class T, unsigned int n>
T PeriodicResponseCurve<T, n>::operator() (const T input) const
{
	T inputInRange = mod(input, getInputMin(), getInputMax());

	return mResponseCurve(inputInRange);
}

template <class T, unsigned int n>
T PeriodicResponseCurve<T, n>::getInputMin() const
{
	return mResponseCurve.getInputMin();
} 

template <class T, unsigned int n>
T PeriodicResponseCurve<T, n>::getInputMax() const
{
	return mResponseCurve.getInputMax();
}

#endif