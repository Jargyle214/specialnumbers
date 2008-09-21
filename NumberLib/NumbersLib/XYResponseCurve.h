#ifndef _XY_RESPONSE_CURVE_H
#define _XY_RESPONSE_CURVE_H

namespace luma
{
namespace numbers
{

template<class T, unsigned int n>
class XYResponseCurve
{
public:
	XYResponseCurve(T inputSamples[n], T outputSamples[n]);
	T operator()(const T input);
	
	void makeInverse();

	/**
		Private: only made public for testing!
	*/
	unsigned int findInputIndex(T input);

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
T XYResponseCurve<T, n>::operator()(const T input)
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
unsigned int XYResponseCurve<T, n>::findInputIndex(T input)
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