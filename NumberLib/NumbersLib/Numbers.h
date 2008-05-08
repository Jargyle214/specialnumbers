#ifndef _NUMBERS_H_
#define _NUMBERS_H_

/**
	Contains classes for wrapping numbers in logic that occur frequently.

	Download the stable version from 
	<a href="http://www.luma.co.za/labs/2007/09/01/c-special-numbers-library/" target="top">
	http://www.luma.co.za/labs/2007/09/01/c-special-numbers-library/</a>
	or get the source code directly from the SVN repository:
	http://code.google.com/p/specialnumbers/.

	@author Herman Tulleken (herman.tulleken@gmail.com)
	@author luma/games (http://www.luma.co.za/)
	@version 1.5
*/

/**
	@mainpage

	This library contains classes for wrapping numbers with logic that reoccur frequently. For
	example, in an application that supports circular scrolling components,
	the code will be riddeled with the following kind of logic:

	@code
	currentSelection = (value + 1) % maxItems;
	...

	//somewhere else
	currentSelection = (currentSelection + maxItems - 1) % maxItems;
	@endcode

	Although this logic is simple, it is error prone. In the preceding example,
	it is easy to forget that the following won't always yield the correct result:

	@code
	currentSelection = (currentSelection - 1) % maxItems;
	@endcode

	The class luma::numbers::CyclicNumber solves this problem by taking care of the logic, alowing us to write:

	@code
	currentSelection++;
	...

	//somewhere else
	currentSelection--;
	@endcode

	Classes provided falls in three categories:
	-	RangedNumber and its subclasses; 
	-	Updateable and its subclasses, as well as BufferedStep; and
	-	AbstractFunction and its subclasses.

	Many classes in this namespace are smart wrappers for primitive types.
	This makes them ideal candidates for operator overloading. However:
	- These classes are used in a specialised way which does not make it useful to
	overload many operators. In fact, many operators may have ambiguous semantics
	for theses classes.
	- In some instances operators might make these classes look too much like
	primitive numbers. This confusion might lead to bugs. See
	BufferedBool for a confusing example.

	Classes can be used with both integer and floating point types, as well as other types
	that satisfy the concept described below. You should only
	use these classes with floating point types if you don't require a lot of precision.
	See BufferedBool for an example of unexpected behaviour with floaing point types.

	@par Using elapsedTime
	You can compensate for slight differences in update rate 
	(typically the frame rate) by passing in the amount of time 
	elapsed since the last update.

	@par
	If you have not used the elapsedTime parameter before, you may want 
	to include a #define for FRAME_RATE so that the new behaviour is roughly
	the same as the old behaviour. FRAME_RATE should be caclulated as follows:
		FRAME_RATE = 1 / averageElapsedTime, 
	where averageElapsedTime is a value emperically measured.

	@par
	If you are starting fresh, you can leave this #define (the default is 1.0f);
	you will simply use a different increments and thresholds than somebody who defined
	FRAME_RATE differently.

	@par Changes Version 1.1:
	-	Made it possible to use all classes in environments 
		where the frame rate is not fixed.
	-	Added DifferentiableNumber.
	-	Minor bug fixes.

	@par Changes Version 1.2
	-	Added IntegrableNumber and PIDBufferedNumber.
	-	Swapped the template parameters of DifferentiableNumber to match ItegrableNumber.

	@par Changes Version 1.3
	-	Added AbstractFilteredNumber and FilteredNumber.
	-	Made IntegrableNumber extend FilteredNumber.
	-	Change some template parameter names to be more readable.
	-	Made IntegrableNumber store it's sum values divided
		by the total time.
	-	Made many methods const.
	-	Added PeriodicResponseCurve.	
	-	Added NumberWrapper.
	
	@par Changes 1.4
	-	Fixed a bug with PingPongNumber

	@par Changes 1.5
	-	Defined UpdateableNumber, a common interface for BufferedNumber, 
		BufferedBool, AbstractFilteredNumber and PIDBufferedNumber.
	-	Changed the getState, setState, and forceState functions of
		BufferedState to getValue, setValue, and forceValue.
	-	Added more documentation
	-	Minor bug fixes with PingPongNumber
	-	Added AbstractFunction and made ResponseCurve and PeriodicResponseCurve
		extends from it.
*/

/**
	Namespace for code developed by Luma. See http://www.luma.co.za/labs/
*/

#ifndef FRAME_RATE
#define FRAME_RATE 1.0f
#endif

#define TIME_UNIT 1.0f

namespace luma
{
	/**
		Namespace for the Numbers library. (See the @ref main page.)
	*/
	namespace numbers
	{
		const float frameRate = FRAME_RATE;
		//const float frameRate = 0.0285f; //Good value for 30 fps
	}
}

#endif //_NUMBERS_H_
