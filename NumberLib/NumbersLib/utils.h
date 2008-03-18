#ifndef _UTILS_H_
#define _UTILS_H_

#include "math.h"

namespace luma
{
namespace numbers
{

template <class T>
inline T min(const T& v1, const T& v2);

template <class T>
inline T max(const T& v1, const T& v2);

/**
	Returns the given value clamped between the given minimum and maximum.

	@param T
		Any type that is supported by the standard min and max functions.
	@param value
		The value to clamp.
	@param minValue
		The minimum value of the output.
	@param maxValue
		The maximum vakue of the output.
	@return
		A value clamped between minValue and maxValue.

	@note The range of this function includes the maxValue.
*/
template <class T>
inline T clamp(const T& value, const T& minValue, const T& maxValue);

/**
	Returns the modulus of a number in a specified range, that is
	(min + value mod (max - min)).

	For example,

	@code
	for (int i = 0; i < 10; i++)
	{
		int r = mod(i, 2, 5);
		cout << i << " ";
	}

	@endcode
	prints 3 4 2 3 4 2 3 4 2 3

	@note The range of this function excludes the maxValue.
*/
template <class T>
inline T mod(const T& value, const T& minValue, const T& maxValue);

/**
	Returns a number reflected between the bounds.

	For example,

	@code
	for (int i = 0; i < 10; i++)
	{
		int r = reflect(i, 0, 3);
		cout << i << " ";
	}

	@endcode
	prints 0 1 2 3 2 1 0 1 2 3

	@note The range of this function includes the maxValue.
*/
template <class T>
inline T reflect(const T& value, const T& minValue, const T& maxValue);


/**
	Linearly interpolates a value between a given range.

	If the value is below the inputMin, the outputMin is returned.
	If the value is above the inputMax, the outputMax is returned.

	Otherwise, the returned value is
	outputMin + ((value - inputMin) / (inputMax - inputMin)) * (outputMax - outputMin).

	@author Luke Lamothe (luke@luma.co.za)
*/
template <class T>
inline T lerp(const T& value, const T& inputMin, const T& inputMax, const T& outputMin, const T& outputMax);

/**
	This function is a smooth aproximation for lerp.
*/
template <class T>
inline T sigmoid(const T& value, const T& inputMin, const T& inputMax, const T& outputMin, const T& outputMax);

/**
	If the value is below the inputMin, the outputMin is returned.

	Otherwise, the returned value is
	outputMin + ((value - inputMin) / (inputMax - inputMin)) * (outputMax - outputMin).
*/
template <class T>
inline T ramp(const T& value, const T& inputMin, const T& inputMax, const T& outputMin, const T& outputMax);

/**
	Otherwise, the returned value is
	outputMin + ((value - inputMin) / (inputMax - inputMin)) * (outputMax - outputMin).
*/
template <class T>
inline T line(const T& value, const T& inputMin, const T& inputMax, const T& outputMin, const T& outputMax);

/**
	Returns the one of two outputs, depending on whether the input value exceeds a given threshold.
*/
template <class T>
inline T step(const T& input, const T& inputThreshold, const T& outputMin, const T& outputMax);

/**
	Returns the fractional part of a float or double. Guarenteed always to lie
	between 0 and 1, even if the input is negative.

	@note: the following identity hold (within floating point threshold):
	@code
		x == frac(c) + floor(x)
	@endcode

	@see floor()
*/
template <class T>
inline T frac(T x);

/**
	Returns the largest integer smaller than the argument given.

	@see frac()
*/
template <class T>
inline T floor(T x);

/**
	Returns the value furthest from the center. For example,
	@code
	extreme(-1, 5, 0) == 5
	extreme(1, -5, 0) == -5
	@endcode

	This is useful, for example when deciding on which of two (polar opposite)
	inputs to use to make a decision.
*/
template <class T>
inline T extreme(T v1, T v2, T center);


//---------------------------------------------------------------------------------------
//	Function definitions
//

template <class T>
inline T min(const T& v1, const T& v2)
{
	return v1 < v2 ? v1 : v2;
}

template <class T>
inline T max(const T& v1, const T& v2)
{
	return v1 > v2 ? v1 : v2;
}


template <class T>
inline T clamp(const T& value, const T& minValue, const T& maxValue)
{
	return min(maxValue, max(minValue, value));
}

template <class T>
inline T mod(const T& value, const T& minValue, const T& maxValue)
{
	T tmpValue = value - minValue;
	T range = maxValue - minValue;

	int quotient = (int)(tmpValue / range);
	T remainder = tmpValue - quotient * range;

	if (remainder < 0)
	{
		remainder += range;
	}

	return minValue + remainder;
}

template <class T>
inline T reflect(const T& value, const T& minValue, const T& maxValue)
{
	T cycleMax = 2 * maxValue - minValue;
	T c = mod(value, minValue, cycleMax);

	return c <= maxValue ? c: 2 * maxValue - c;
}


template <class T>
inline T lerp(const T& value, const T& inputMin, const T& inputMax, const T& outputMin, const T& outputMax)
{
	if(value >= inputMax)
	{
		return outputMax;
	}

	return ramp(value, inputMin, inputMax, outputMin, outputMax);
}

template <class T>
inline T sigmoid(const T& value, const T& inputMin, const T& inputMax, const T& outputMin, const T& outputMax)
{
	T w = exp((-2 * value + (inputMax + inputMin))/ (inputMax - inputMin));

	return (outputMax - outputMin) / (1 + w) + outputMin;
}

template <class T>
inline T ramp(const T& value, const T& inputMin, const T& inputMax, const T& outputMin, const T& outputMax)
{
	if(value <= inputMin)
	{
		return outputMin;
	}

	return line(value, inputMin, inputMax, outputMin, outputMax);
}

template <class T>
inline T line(const T& value, const T& inputMin, const T& inputMax, const T& outputMin, const T& outputMax)
{
	return outputMin + ((value - inputMin) * (outputMax - outputMin) / (inputMax - inputMin));
}

template <class T>
inline T frac(T x)
{
	return x >= (T) 0 ? x - (int) x : x + 1 - (int) x;
}

template <class T>
inline T floor(T x)
{
	return x >= (T) 0 ? (int) x : (int) x - 1;
}

template <class T>
inline T extreme(T v1, T v2, T center = 0)
{
	return abs(v1 - center) > abs(v2 - center) ? v1 : v2;
}

template <class T>
inline T step(const T& input, const T& inputThreshold, const T& outputMin, const T& outputMax)
{
	return input < inputThreshold ? outputMin : outputMax;
}


}} //namespace
#endif //_UTILS_H_
