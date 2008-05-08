#ifndef _ABSTRACT_FUNCTION_H_
#define _ABSTRACT_FUNCTION_H_

namespace luma
{
namespace numbers
{

/**
	Simply a class that implements the function call operator, and used 
	to implement (mathematical) functions.
*/
template <class T>
class AbstractFunction
{
public:
	/**
		Returns an output value that depends on the input value.

		@param input
			The input for which output is sought.
	*/
	virtual T operator()(const T input) const = 0;
};

}}

#endif //_ABSTRACT_FUNCTION_H_