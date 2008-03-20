#ifndef _RESPONSE_CURVE_H
#define _RESPONSE_CURVE_H

namespace luma
{
namespace numbers
{

/**
	This class is described in AI Programming Wisdom 1, "The Beauty of Response Curves", by Bob Alexander.

	@param n 
		Number of output samples.
	@param T
		The number type of the input and output, usually float or double.
*/
template <unsigned int n, class T>
class ResponseCurve
{
public:
	/**
		Constructs a new TransferFunction.
		
		@param inputMin
			The minimum value an input can be. 
		@param inputMax
			The maximum value an input can be.
		@param outputSamples
			Samples of outputs.
	*/
	ResponseCurve(T inputMin, T inputMax, T outputSamples[n]);

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
	T operator()(const T input);

	inline public T getInputMin();
	inline public T getInputMax();

private:
	T mInputMin;
	T mInputMax;
	T mOutputSamples[n];

	/**
		The difference between two adjacent input values 
		at sample points.
	*/
	T mPeriod;
};

template <unsigned int n, class T>
ResponseCurve<n, T>::ResponseCurve(T inputMin, T inputMax, T outputSamples[n]):
	mInputMin(inputMin),
	mInputMax(inputMax),
	mPeriod((inputMax - inputMin) / (n - 1))
{
	for(unsigned int i = 0; i < n; i++)
	{
		mOutputSamples[i] = outputSamples[i];
	}
}

template <unsigned int n, class T>
T ResponseCurve<n, T>::operator()(const T input)
{
	if(input <= mInputMin)
	{
		return mOutputSamples[0];
	}

	if(input >= mInputMax)
	{
		return mOutputSamples[n - 1];
	}

	unsigned int index = (int) ((input - mInputMin)/(mPeriod));
	T inputSampleMin = mInputMin + mPeriod*index;

	return lerp(input, inputSampleMin, inputSampleMin + mPeriod, mOutputSamples[index], mOutputSamples[index + 1]);
}

template <unsigned int n, class T>
T ResponseCurve<n, T>::getInputMin()
{
	return mInputMin;
} 

template <unsigned int n, class T>
T ResponseCurve<n, T>::getInputMax()
{
	return mInputMax;
}

};}; //namespace

#endif //_RESPONSE_CURVE_H