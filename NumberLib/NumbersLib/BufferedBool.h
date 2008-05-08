#ifndef _BUFFERED_BOOL_
#define _BUFFERED_BOOL_

#include "ClampedNumber.h"
#include "UpdateableNumber.h"

namespace luma
{
namespace numbers
{

/**
	This class can be used instead of a bool to get smoother (less eratic) transitions,
	that is, the value stays true or false longer. It works as follows: an internal value is
	maintained. Every time this class is set to true, the value is increased; every time
	it is set to false, that value is reduced. When the value becomes larger than a certain
	threshold, the output value is switched to true. Similarly when the value becomes smaller
	than a certain threshold, the output value is switched to false. These two thresholds needn't
	(and in most cases shouldn't) be the same.

	This class is supposed to mimick bools. However, assignement and other operators have not been
	overloaded so that this class won't be confused with an actual bool.

	For example, suppose the internal float value is well below the threshold. Then the following code results
	print "false";

	b.setValue(true)
	printf(b.getValue() ? "true" : "false");


	If we overloaded the operators, we would get

	b = false;
	printf(b ? "true" : "false");

	which would be more confusing. The less convenient but explicit syntax reminds us that this is not pure
	bool, but something special.

	Using with floating point

	Consider this example:

	@code

		BufferedBool b(0.3f, 0.7f, 0.1f);

		for(int i = 0; i < 8; i++)
		{
			b.setValue(true);
			cout << b.getValue() << " ";
		}
	@endcode

	This will print
	@code
	false false false false false false true true
	@endcode
	instead of
	@code
	false false false false false false false true
	@endcode

	This is because the top threshold is converted to .69999999 and adding the increment
	0.1 seven times is to 0 gives 0.70000005, so the internal float becomes greater than
	the threshold one iteration too early. Never rely on exact transitions!

	@author Herman Tulleken (herman.tulleken@gmail.com)
	@author luma/games (http://www.luma.co.za/)
*/

	class BufferedBool : UpdateableNumber<bool>
{
private:
	float mBottomThreshold;
	float mTopThreshold;
	ClampedNumber<float> mFloatValue;
	bool mBoolValue;
	float mFrameTime;

public:
	/**
		Constructs a new BufferedBool.

		@param bottomThreshold
			if the internal float value drops below this point,
			the bool value next returned will be false.

		@param topThreshold
			if the internal float value rises above this point,
			the bool value next returned will be true.

		@param increment
			The value with which the internal float is adjusted
			each time setValue() is called.
	*/
	BufferedBool(float bottomThreshold, float topThreshold, float increment = 0.1f);

	/**
		Returns the boolean value, which depends on which threshold was
		last triggered.
	*/
	bool getValue() const;

	/**
		The internal float is incremented if this is true, otherwise it is decremented. If one
		of the thresholds is triggered, the boolean value is adjusted accordingly.
	*/
	void setValue(bool value, float ellapsedTime = 1);

	/**
		Forces the next value to be the given value.
	*/
	void forceValue(bool value);

	/**
		Sets the uincreemnt value for this buffered bool. In general, 
		the larger this value, the quicker the bool will chnage states.
	*/
	void setIncrement(float increment);

	/**
		Returns the internal float value that regulates the boolean
		value. This function is useful for debugging.
	*/
	float getFloatValue() const;

};
}}//namespace

#endif //_BUFFERED_BOOL_
