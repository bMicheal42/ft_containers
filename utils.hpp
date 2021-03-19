#pragma once

namespace ft {

	template <typename T>
	bool	my_comp(const T &a, const T &b) {
		return (a > b);
	}

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
	template <bool isConst, typename isFalse, typename isTrue>
	struct chooseConst {};


	template <typename isFalse, typename isTrue> //non-const
	struct chooseConst<false, isFalse, isTrue>
	{
		typedef isFalse type;
	};

	template <typename isFalse, typename isTrue> //const
	struct chooseConst<true, isFalse, isTrue>
	{
		typedef isTrue type;
	};

/*
================================================================================
*/

	template <typename E1, typename  E2>
	class pair
	{

	public:
		E1 first;
		E2 second;

		pair() : first(), second() {}

		pair(const E1 &a, const E2 &b) : first(a), second(b) {}

		template <typename C1, typename C2>
		pair(const pair<C1, C2> &copy) : first(copy.first), second(copy.second) {};

		~pair() {};

		pair &operator=(const pair &add)
		{
			if (this != &add)
			{
				first = add.first;
				second = add.second;
			}
			return (*this);
		}
	};
} // end of namespace