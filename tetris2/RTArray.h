#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <new>
#include <mutex>


template<class T>
std::unique_ptr<T[]> New1DArray(const unsigned int _Length)
{
	std::unique_ptr<T[]> array(new (std::nothrow) T[_Length]());

	return(array);
}


template<class T>
std::unique_ptr<std::unique_ptr<T[]>[]> New2DArray(const unsigned int _Length, const unsigned int _Width)
{
	auto array2(New1DArray<std::unique_ptr<T[]>>(_Length));

	for (unsigned int index = 0; index < _Length; ++index)
	{
		auto array(New1DArray<T>(_Width));

		array2[index].swap(array);
	}

	return(array2);
}


template<class T>
std::unique_ptr<std::unique_ptr<std::unique_ptr<T[]>[]>[]> New3DArray(const unsigned int _Length, const unsigned int _Width, const unsigned int _Height)
{
	auto array3(New1DArray<std::unique_ptr<std::unique_ptr<T[]>[]>>(_Length));

	for (unsigned int index = 0; index < _Length; ++index)
	{
		auto array2(New2DArray<T>(_Width, _Height));

		array3[index].swap(array2);
	}

	return(array3);
}


#endif

