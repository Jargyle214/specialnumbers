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
template <class T, unsigned int n>
class DifferentiableNumber
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
	DifferentiableNumber<T, n - 1> mDifference;

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
	T getValue(unsigned int m = 0) const;

	/**
		Force this number to the given value. 
		Internal derivative are forced to 0.
	*/

	void forceValue(T value);
};

template <class T, unsigned int n>
void DifferentiableNumber<T, n>::setValue(T value, float elapsedTime)
{
	mPreviousValue = mValue;
	mValue = value;

	mDifference.setValue((mValue - mPreviousValue) / (elapsedTime * frameRate));
}

template <class T, unsigned int n>
void DifferentiableNumber<T, n>::forceValue(T value)
{
	mPreviousValue = value;
	mValue = value;

	mDifference.forceValue(mInitialValue);
}

template <class T, unsigned int n>
DifferentiableNumber<T, n>::DifferentiableNumber(T initialValue):
	mInitialValue(initialValue),
	mValue(initialValue),
	mPreviousValue(initialValue),
	mDifference(initialValue)
{
}

template <class T, unsigned int n>
T DifferentiableNumber<T, n>::getValue(unsigned int m) const
{
	if(m == 0)
	{
		return mValue;
	}
	else if(m > 0)
	{
		if(m <= n)
		{
			return mDifference.getValue(m - 1);
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
class DifferentiableNumber<T, 1>
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
	T getValue(unsigned int m = 0) const;
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
T DifferentiableNumber<T, 1>::getValue(unsigned int m) const
{
	if(m == 0)
	{
		return mValue;
	}
	else if(m == 1)
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
class DifferentiableNumber<T, 0>
{
private:
	T mValue;
	T mInitialValue;
public:
	DifferentiableNumber(T initialValue);

	/**
		Sets the current value of this DifferentiableNumber.
		The elapsedTime variable is ignored.
	*/
	void setValue(T value, float elapsedTime = 1.0f);

	/**
		Only m = 0 will give anything other than the 
		initialValue.
	*/
	T getValue(unsigned int m = 0) const;

	void forceValue(T value);
};

template <class T>
void DifferentiableNumber<T, 0>::setValue(T value, float)
{	
	mValue = value;	
}

template <class T>
void DifferentiableNumber<T, 0>::forceValue(T value)
{	
	mValue = value;	
}

template <class T>
DifferentiableNumber<T, 0>::DifferentiableNumber(T initialValue):
	mInitialValue(initialValue),
	mValue(initialValue)
{
}

template <class T>
T DifferentiableNumber<T, 0>::getValue(unsigned int m) const
{
	if(m == 0)
	{
		return mValue;
	}	

	return mInitialValue;
}

};};

#endif //_DIFFERENTIABLE_NUMBER_H_