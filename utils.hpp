#pragma once

#include "utility"
#include <iterator>

namespace ft {

	template<class InputIterator1, class InputIterator2>
	bool            equalx(InputIterator1 first1, InputIterator1 last1,
						InputIterator2 first2, InputIterator2 last2)
	{
		while ((first1 != last1) && (first2 != last2))
		{
			if (*first1 != *first2)
				return false;
			++first1;
			++first2;
		}
		return (first1 == last1) && (first2 == last2);
	}
/*
================================================================================
*/
	template<class T>
	struct less
	{
		bool  operator()(const T &a, const T &b) const
		{
			return a < b;
		}
	};
/*
================================================================================
*/
	template<class Key, class T>
	struct less_key
	{
		bool  operator()(const std::pair<const Key, T> &a, const std::pair<const Key, T> &b) const
		{
			return a.first < b.first;
		}

		bool  operator()(const Key &a, const Key &b) const
		{
			return a < b;
		}
	};
/*
================================================================================
*/
	template<bool B, class T = void>
	struct enable_if
	{
	};

	template<class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};
/*
================================================================================
*/
} // end of namespace

# define fl std // just a joke