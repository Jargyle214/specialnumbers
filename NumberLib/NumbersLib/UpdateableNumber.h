#ifndef _UPDATEABLE_NUMBER_H_
#define _UPDATEABLE_NUMBER_H_

namespace luma
{
namespace numbers
{

/**
	Updateable numbers are used when a value is updated regularly, 
	and logic should be	performed on every update.

	This is a typical example of how to use any updateable number:

	//declaration
	BufferedNumber<float> filteredSpeed(0.0f, -100.0f, 100.0f, 0.5f);

	@code
	// General update method - called every tick
	void update()
	{
		filteredSpeed.setValue(getSpeed());

		//update, for example, a GUI widget based on the filteredValue.
		speedWidget.setDisplayValue(filteredSpeed.getValue());
	}
	@endcode

	In general, setValue should only be called once per update, but getValue
	can be called any number of times.

	@note BufferedStep works like Updateable numbers, although
	the class does not implement the Updateable interface.

	@note Boolean values, and enums are also considered "numbers".


*/
template <class T>
class UpdateableNumber
{
public:
	/**
		Get the current value of this AbstractFilteredNumber of the given order.
	*/
	virtual T getValue() const = 0;

	/**
		Sets a new input value. In general, this function should only be called 
		once per update.
	*/
	virtual void setValue(T value, float elapsedTime=TIME_UNIT) = 0;
};


}}//namespace
#endif //_UPDATEABLE_NUMBER_H_