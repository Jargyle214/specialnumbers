#ifndef _PID_BUFFERED_NUMBER_H
#define _PID_BUFFERED_NUMBER_H

#include "DifferentiableNumber.h"
#include "IntegrableNumber.h"

namespace luma
{
namespace numbers
{

/**
	A PIDBufferedNumber is a simple PID controller.

	Let D_n be the nth differential, I_n be the nth integral, then the value
	returned by getValue() is

	@code
	y = a * x + b_1*D_1[x] + b_2*D_2[x] + ... + c_1*I_1[x] + c_2*I_2[x] + ...
	@endcode

	@param T
		The variable type of this PIDBufferedNumber, typically float.
	@param dn
		The number of derivatives that will be used.
	@param in 
		The number of integrals that will be used.
	@param im
		The number of samples over hwich the integration will be.
*/
template<class T, unsigned int dn, unsigned int in, unsigned int im>
class PIDBufferedNumber
{
private:
	/** The current value*/
	T mValue;

	/** The differentiable presentation of the value */
	DifferentiableNumber<T, dn> mDifferentiableValue;

	/** The itegrable presentation of the value*/
	IntegrableNumber<T, im, in> mIntegrableValue;
		
	/** Factor by which the current value is multiplied.*/ 
	T mValueFactor;

	/** Factors by which differentials are multiplied.*/
	T mDifferentiableValueFactors[dn];

	/** Factors by which integrals are multiplied.*/
	T mIntegrableValueFactors[in];	

public:

	/** Constructs a new PIDBufferedNumber. 
		@param initialValue
			Zero of type T. The value, all differentials and 
			all integrals are initialised with this value
		
		@param valueFactor
			The factor by which the current value is multiplied 
			in the getValue() function.

		@param differentiableValueFactors
			Factors by which derrivatives are multiplied
			in the getValue() function.

		@param integrableValueFactors
			Factors by which integrals are multiplied
			in the getValue() function.			
	*/
	PIDBufferedNumber(T initialValue, T valueFactor,
		T differentiableValueFactors[dn], T integrableValueFactors[in]);

	/**
		Sets the current value of this PIDBufferedNumber.
	*/
	void setValue(T x, float elapsedTime = 1.0f);

	/**
		Sets the current value of this PIDBufferedNumber.
	*/
	void forceValue(T x, float elapsedTime = 1.0f);

	/**
		Returns a weighted sum of the current value, 
		its derivatives, and its integrals. The weights 
		are the factors passed in to the constructor.
	*/
	T getValue() const;

	T getSample(int i) const;

	/**
	Forces this controller to the given value. This means
	all samples are forced to this value.
	*/

};

template<class T, unsigned int dn, unsigned int in, unsigned int im>
PIDBufferedNumber<T, dn, in, im>::PIDBufferedNumber(
	T initialValue, 
	T valueFactor,
	T differentiableValueFactors[dn],
	T integrableValueFactors[in]):
	mDifferentiableValue(initialValue),
	mIntegrableValue(initialValue),
	mValue(initialValue),
	mValueFactor(valueFactor)
{
	for(int i = 0; i < dn; i++)
	{
		mDifferentiableValueFactors[i] = differentiableValueFactors[i];
	}

	for(int i = 0; i < in; i++)
	{
		mIntegrableValueFactors[i] = integrableValueFactors[i];
	}
}

template<class T, unsigned int dn, unsigned int in, unsigned int im>
void PIDBufferedNumber<T, dn, in, im>::setValue(T x, float elapsedTime)
{
	mValue = x;
	mDifferentiableValue.setValue(x, elapsedTime);
	mIntegrableValue.setValue(x, elapsedTime);
}

template<class T, unsigned int dn, unsigned int in, unsigned int im>
void PIDBufferedNumber<T, dn, in, im>::forceValue(T x, float elapsedTime)
{
	mValue = x;
	mDifferentiableValue.forceValue(x);
	mIntegrableValue.forceValue(x, elapsedTime);
}

template<class T, unsigned int dn, unsigned int in, unsigned int im>
T PIDBufferedNumber<T, dn, in, im>::getValue() const
{
	T sum = mValue * mValueFactor;

	for(int i = 0; i < dn; i++)
	{
		sum += mDifferentiableValueFactors[i] * mDifferentiableValue.getValue(i + 1);
	}

	for(int i = 0; i < in; i++)
	{
		sum += mIntegrableValueFactors[i] * mIntegrableValue.getValue(i + 1);
	}
	
	return sum;
}

template<class T, unsigned int dn, unsigned int in, unsigned int im>
T PIDBufferedNumber<T, dn, in, im>::getSample(int i) const
{
	return mIntegrableValue.getSample(i);
}

}}

#endif //_PID_BUFFERED_NUMBER_H