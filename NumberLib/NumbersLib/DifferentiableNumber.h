#ifndef _DIFFERENTIABLE_NUMBER_H_
#define _DIFFERENTIABLE_NUMBER_H_

namespace luma
{
namespace numbers
{

/**
	A DifferentiableNumber is a number that keeps track of 
	its own derivatives. These are calculated every time 
	the number's value is set.

	@f[
	y_n = \Delta x_n = \frac{x_n - x_{n-1}}{t_n}
	@f]

	The maximum order of differentiation that will be required
	is set as one of the template parameters. The intitial value
	with which the DifferentiableNumber is initialised is returned
	for any differential requested that was not computed for this 
	differentiable number. 
	
	For example:
	
	@code

	DifferentiableNumber<3, float> n(0);

	...
	//set the value a few times
	...

	float m = n.getValue(4); //m is 0
	@endcode
	
	This class is to be used in simulations. For example, if 
	position was declared as follows:
	
	@code
	Differentiable<2, Vector2> position (Vector2(0, 0));
	@endcode

	and the position is updated every frame, then

		-	@code position.getValue(0) @endcode gives the position
		-	@code position.getValue(1) @endcode gives the velocity
		-	@code position.getValue(2) @endcode gives the acceleration.

	The advantage of using this class instead of the usual logic
	is that it saves a lot of code, and related updates are done in 
	one place. Of course there is some overhead involved.

	@see IntegrableNumber
*/
template <class T, unsigned int maxOrder>
class DifferentiableNumber : public AbstractFilteredNumber<T, 2, maxOrder>
{
private:
	T mValue;
	T mPreviousValue;	
	T mInitialValue; //some sort of 0

	/** 
		The difference between the current and previous values is
		maintained as a DifferentiableNumber<n - 1, T>. It will keep
		track of its own derivatives.
	*/
	DifferentiableNumber<T, maxOrder - 1> mDifference;

public:
	/**
		Constructs a new DifferentiableNumber with the
		initialValue. Note that this should be a form of 
		0. If T is a Vector2 type, the initialValue 
		should be (0, 0).
	*/
	DifferentiableNumber(T initialValue);

	/**
		Sets the value for this DifferentiableNumber.

		@param elapsedTime
			The amount of thime passed since the last update.
	*/
	void setValue(T value, float elapsedTime = 1.0f);

	/** 
		Gets the value of the mth derivative of this 
		DifferentiableNumber.
		
		@param m 
			The order of the derivative for this 
			DifferentiableNumber to get the value of. If m == 0,
			the current value is returned.
	*/
	T getValue(unsigned int order = 1) const;

	/**
		Force this number to the given value. 
		Internal derivative are forced to 0.
	*/

	void forceValue(T value);
};

template <class T, unsigned int maxOrder>
void DifferentiableNumber<T, maxOrder>::setValue(T value, float elapsedTime)
{
	mPreviousValue = mValue;
	mValue = value;

	mDifference.setValue((mValue - mPreviousValue) / (elapsedTime * frameRate));
}

template <class T, unsigned int maxOrder>
void DifferentiableNumber<T, maxOrder>::forceValue(T value)
{
	mPreviousValue = value;
	mValue = value;

	mDifference.forceValue(mInitialValue);
}

template <class T, unsigned int maxOrder>
DifferentiableNumber<T, maxOrder>::DifferentiableNumber(T initialValue):
	mInitialValue(initialValue),
	mValue(initialValue),
	mPreviousValue(initialValue),
	mDifference(initialValue)
{
}

template <class T, unsigned int maxOrder>
T DifferentiableNumber<T, maxOrder>::getValue(unsigned int order) const
{
	if(order == 0)
	{
		return mValue;
	}
	else if(order > 0)
	{
		if(order <= maxOrder)
		{
			return mDifference.getValue(order - 1);
		}
	}

	return mInitialValue;
}

/**
	This is the stop class for the recursive template definition of
	DifferentiableNumber. All the methods work the same as
	DifferentiableNumber - see the documentation there.
*/
template <class T>
class DifferentiableNumber<T, 1> : public AbstractFilteredNumber<T, 2, 1>
{
private:
	T mValue;
	T mPreviousValue;
	T mDifference;
	T mInitialValue;

public:
	
	/**
	@see DifferentiableNumber<T, n>::DifferentiableNumber()
	*/
	DifferentiableNumber(T initialValue);

	/**
	@see DifferentiableNumber<T, n>::setValue()
	*/
	void setValue(T value, float elapsedTime = 1.0f);

	void forceValue(T value);

	/**
	@see DifferentiableNumber<T, n>::getValue()
	*/
	T getValue(unsigned int order = 1) const;
};

template <class T>
void DifferentiableNumber<T, 1>::setValue(T value, float elapsedTime)
{
	mPreviousValue = mValue;
	mValue = value;
	mDifference = (mValue - mPreviousValue) / (elapsedTime * frameRate);
}

template <class T>
void DifferentiableNumber<T, 1>::forceValue(T value)
{
	mPreviousValue = value;
	mValue = value;
	mDifference = mInitialValue;
}


template <class T>
DifferentiableNumber<T, 1>::DifferentiableNumber(T initialValue):
	mInitialValue(initialValue),
	mValue(initialValue),
	mPreviousValue(initialValue),
	mDifference(initialValue)
{
}

template <class T>
T DifferentiableNumber<T, 1>::getValue(unsigned int order) const
{
	if(order == 0)
	{
		return mValue;
	}
	else if(order == 1)
	{
		return mDifference;		
	}
	
	return mInitialValue;
}

/**
	This specialisation is provided for completeness' sake and should
	generally not be used. It is nothing more than a wrapper for the value;
	the elapsedTime is ignored.
*/
template <class T>
class DifferentiableNumber<T, 0> : public AbstractFilteredNumber<T, 2, 0>
{
private:
	T mValue;
	T mInitialValue;
public:
	DifferentiableNumber(T initialValue);
};


template <class T>
DifferentiableNumber<T, 0>::DifferentiableNumber(T initialValue):
	AbstractFilteredNumber(initialValue)
{
}

};};

#endif //_DIFFERENTIABLE_NUMBER_H_