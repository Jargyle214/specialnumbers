#ifndef _XY_RESPONSE_CURVE_H
#define _XY_RESPONSE_CURVE_H

#include "AbstractFunction.h"

namespace luma
{
namespace numbers
{
/**
	Similar to ResponseCurve, but allows sample points to be unevenly spaced.

	This curve is slower than the ordinary ResponseCurve. However, it is useful 
	for generating the inverse of a monotonic function. For rapid access, this 
	curve should be sampled into a ordinary ResponseCurve.
*/
template<class T, unsigned int n>
class XYResponseCurve: public AbstractFunction<T>
{
public:
	/**
		Construct a new XYResponse curve from input and output samples.

		@param inputSamples
			The input values for this response curve. Must be strictly increasing.

		@param outputSamples
			The output vlaues for this curve.
	*/
	XYResponseCurve(T inputSamples[n], T outputSamples[n]);

	/**
		If the input is below the inputMin given in the constructor, 
		the output is clamped to the first output sample.

		If the input is above the inputMax given in the constructor,
		the output is clamped to the last output sample.

		Otherwise an index is calculated, and the output is interpolated
		between outputSample[index] and outputSample[index + 1].

		@param input
			The input for which output is sought.
	*/
	T operator()(const T input) const;
	
	void makeInverse();

	/**
		Private: only made public for testing! Test which input sample lies to the left of the given input.
	*/
	unsigned int findInputIndex(const T input) const;

private:
	T mInputSamples[n];
	T mOutputSamples[n];
	
};

template<class T, unsigned int n> 
XYResponseCurve<T, n>::XYResponseCurve(T inputSamples[n], T outputSamples[n])
{
	for(unsigned i = 0; i < n; i++)
	{
		mInputSamples[i] = inputSamples[i];
		mOutputSamples[i] = outputSamples[i];
	}
}

template<class T, unsigned int n> 
T XYResponseCurve<T, n>::operator()(const T input) const
{
	if (input <= mInputSamples[0])
	{
		return mOutputSamples[0];
	}

	if (input >= mInputSamples[n - 1])
	{
		return mOutputSamples[n - 1];
	}

	unsigned int index = findInputIndex(input);


	T x1 = mInputSamples[index + 1];
	T x0 = mInputSamples[index];

	T tau = (input - x0) / (x1 - x0);
	T y1 = mOutputSamples[index + 1];
	T y0 = mOutputSamples[index];
	return (y1 - y0) * tau + y0;
}

template<class T, unsigned int n> 
unsigned int XYResponseCurve<T, n>::findInputIndex(const T input) const
{
	unsigned int min = 0;
	unsigned int max = n;
	unsigned int mid;

	while (max > min + 1)
	{
		mid = (max + min) / 2 ;
		//printf("mmm: %d %d %d\n", min, mid, max);

		if(input < mInputSamples[mid])
		{
			max = mid;
		}
		else
		{
			min = mid;
		}	
	}

	return min;
}
template<class T, unsigned int n> 
void XYResponseCurve<T, n>::makeInverse()
{
	T tmp;

	for (unsigned i = 0; i < n; i++)
	{
		tmp = mInputSamples[i];
		mInputSamples[i] = mOutputSamples[i];
		mOutputSamples[i] = tmp;
	}
}


}
}

#endif //_XYRESPONSE_CURVE_H