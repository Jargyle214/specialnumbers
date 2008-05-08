#ifndef _BUFFERED_STATE_H
#define _BUFFERED_STATE_H

#include "Numbers.h"
#include "ClampedNumber.h"

namespace luma
{
namespace numbers
{

/**
	This class handles buffered states transitions, that is, it can be used to 
	reduce state flickering. It is is useful in cases where transition checks 
	should consistently indicate a state change before the actual state change 
	takes place.

	This class assumes all states lie in the range [0, n). The function setValue(i) is
	called to indicate the check for transition to state i has succeeded. Similarly,
	if getValue() returns i, the state should change to state i. 

	Note that this class is not a state machine - rather, it can be used with a state 
	machine to gain buffered transitions.

	@param n 
		The number of states.

	@author Herman Tulleken (herman.tulleken@gmail.com)
	@author luma/games (http://www.luma.co.za/)

*/
template <unsigned int n>
class BufferedState : public UpdateableNumber<unsigned int>
{
private:

	/**
		This class is provided solely so that we can have a 
		default constructor, and can hence use this class in
		an array.
	*/
	class DefaultClampedFloat : public ClampedNumber<float>
	{
	public:
		/**
			Constructs a new DefaultClampedFloat.
		*/
		DefaultClampedFloat(float increment = 0.1f);
		
		/**
			Sets the increment for this DefaultClampedFloat.
		*/
		void setIncrement(float increment);

		/**
			Assigns the given value to this DefaultClampedFloat.
		*/
		//DefaultClampedFloat& operator=(const float& value);
	
	};

	DefaultClampedFloat mStateValues[n];
	float mThresholds[n];
	unsigned int mState;

public:

	/**
		Initialises a new BufferedState.

		@param initialState
			the initial state

		@param stateValues
			the initial state values. Usually, if initialState is i, 
			then initialStates[i] = 1.0f and 
			initialStates[j] = 0.0 if j != i. 

		@param thresholds
			the triggering thresholds for each state. Each of these should be greater
			than 0.5f, otherwise flickering might still occur. A state triggers if
			is stateValue is greater than this threshold.

		@param increment
			this is the value added or subtracted from state values everytime the setValue
			function is called.
	*/
	BufferedState(unsigned int initialState, float stateValues[], float thresholds[], float increment);

	/**
		Copy constructor.

		@note All internal vectors are copied, so that this data is not shared.
	*/
	BufferedState(const BufferedState& other);

	/**
		Sets the state of this buffered state. Note that setting the state does not
		mean that state will be returned next by getState(). This will only happen 
		after a number of calls to setState, depending on the thresholds and increment.
	*/
	void setValue(unsigned int state, float ellapsedTime = 1);

	/**
		Returns the last triggered state.
	*/
	unsigned int getValue() const;

	/**
		Forces the state to the given state. 
	*/
	void forceValue(int state);
};

template <unsigned int n>
BufferedState<n>::DefaultClampedFloat::DefaultClampedFloat(float increment):
	ClampedNumber<float>(0.0f, 0.0f, 1.0f, increment)
{};
		
template <unsigned int n>
void BufferedState<n>::DefaultClampedFloat::setIncrement(float increment)
{
	modify(mMin, mMax, increment);
}

/*template <unsigned int n>
typename BufferedState<n>::DefaultClampedFloat& BufferedState<n>::DefaultClampedFloat::operator=(const float& value)
{
	return dynamic_cast<DefaultClampedFloat&>(ClampedNumber<float>::operator=(value));
}*/

template <unsigned int n>
BufferedState<n>::BufferedState(unsigned int initialState, float stateValues[], float thresholds[], float increment):
	mState(initialState)
{
	for (unsigned int i = 0; i < n; i++)
	{
		mStateValues[i].setIncrement(increment);
		mStateValues[i].setValue(stateValues[i]);
		mThresholds[i] = thresholds[i];
	}
}

template <unsigned int n>
BufferedState<n>::BufferedState(const BufferedState& other):
	mState(other.mState)
{
	for (unsigned int i = 0; i < n; i++)
	{
		mStateValues[i] = other.mStateValues[i];
		mThresholds[i] = other.mThresholds[i];
	}
}

template <unsigned int n>
void BufferedState<n>::setValue(unsigned int state, float ellapsedTime)
{
	mStateValues[state].inc(ellapsedTime);

	if(mStateValues[state] > mThresholds[state])
		mState = state;

	for (unsigned int i = 0; i < n; i++)
	{
		if(i == state)
			continue;
		
		mStateValues[i].dec(ellapsedTime);
	}
}

template <unsigned int n>
unsigned int BufferedState<n>::getValue() const
{
	return mState;
}

template <unsigned int n>
void BufferedState<n>::forceValue(int state)
{
	mState = state;

	for (int i = 0; i < n; i++)
	{
		mStateValues[i] = (i == state ? 1.0f : 0.0f);
	}
}
};};//namespace

#endif //_BUFFERED_N_STATE_H