#pragma once

namespace ft {

	template<bool B, class T = void>
	struct enable_if
	{
	};

	template<class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};


	template <typename E1, typename  E2>
	class pair
	{

	public:
		E1 element1;
		E2 element2;

		pair() :element1(), element2() {}

		pair(const E1 &a, const E2 &b) :element1(a), element2(b) {}

		template <typename C1, typename C2>
		pair(const pair<C1, C2> &copy) : element1(copy.element1), element2(copy.element2) {};

		~pair() {};

		pair &operator=(const pair &add)
		{
			if (this != &add)
			{
				element1 = add.element1;
				element2 = add.element2;
			}
			return (*this);
		}
	};
} // end of namespace