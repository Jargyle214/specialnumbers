#ifndef _NUMBER_WRAPPER_H_
#define _NUMBER_WRAPPER_H_

namespace luma{
namespace numbers {

template <class T>
class NumberWrapper
{
public:
	NumberWrapper(T value);
	NumberWrapper(T value, T min, T max, T increment);

	void setValue(T value, float elapsedTime = 1.0f);
	T getValue() const;

private:
	T mValue;
};

template <class T>
NumberWrapper<T>::NumberWrapper(T value):
	mValue(value)
{
}

template <class T>
NumberWrapper<T>::NumberWrapper(T value, T, T, T):
	mValue(value)
{
}

template <class T>
void NumberWrapper<T>::setValue(T value, float)
{
	mValue = value;
}

template <class T>
T NumberWrapper<T>::getValue() const
{
	return mValue;
}

}}



#endif _NUMBER_WRAPPER_H_