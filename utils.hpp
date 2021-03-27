#pragma once

namespace ft {

	template<class InputIterator1, class InputIterator2>
	bool			equalx(InputIterator1 first1, InputIterator1 last1,
						   InputIterator2 first2, InputIterator2 last2) {
		while ((first1 != last1) && (first2 != last2)) {
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

//	template <typename E1, typename  E2>
//	class pair
//	{
//
//	public:
//		E1 first;
//		E2 second;
//
//		pair() : first(), second() {}
//
//		pair(const E1 &a, const E2 &b) : first(a), second(b) {}
//
//		template <typename C1, typename C2>
//		pair(const pair<C1, C2> &copy) : first(copy.first), second(copy.second) {};
//
//		~pair() {};
//
//		pair &operator=(const pair &add)
//		{
//			if (this != &add)
//			{
//				first = add.first;
//				second = add.second;
//			}
//			return (*this);
//		}
//	}; //end of pair class

} // end of namespace

# define fl std //for peers
//# define ft ft //classic