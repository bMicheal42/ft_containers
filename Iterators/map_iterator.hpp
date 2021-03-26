#pragma once

#include "vector_iterator.hpp"

namespace ft {

// =============================================================================
	/** ---------------------------- MULTISET_ITERATOR ---------------------- */
// =============================================================================
	template<typename T, typename Pointer = T*, typename Reference = T&>
	class multiset_iterator
	{

	public:
		typedef std::bidirectional_iterator_tag				iterator_category;
		typedef T											value_type;
		typedef Pointer										pointer;
		typedef Reference									reference;
		typedef ptrdiff_t									difference_type;
		typedef size_t										size_type;

// ====================== CONSTRUCTORS / DESTRUCTOR ============================

		multiset_iterator() :it() {}

		multiset_iterator(vector_iterator<T> v_it) :it(v_it) {} //обоснуй

		multiset_iterator(multiset_iterator<T, T*, T&> const &copy) :it(copy.getIt()) {}

		~multiset_iterator() {}
// ============================ OPERATORS ======================================

		vector_iterator<T>	getIt() const
		{
			return this->it;
		}

		// '='
		multiset_iterator		&operator=(multiset_iterator const &other)
		{
			if (&other != this)
				it = other.it;
			return (*this);
		}

		// '*'
		reference			operator*() const { return (*this->it); }

		// '->'
		pointer				operator->() { return (this->it.base()); }

		// '++ pre'
		multiset_iterator 	&operator++()
		{
			++this->it;
			return (*this);
		}

		// '++ post'
		multiset_iterator		operator++(int)
		{
			multiset_iterator tmp(*this);
			++this->it;
			return (tmp);
		}

		// '-- pre'
		multiset_iterator		&operator--()
		{
			--this->it;
			return (*this);
		}

		// '-- post'
		multiset_iterator		operator--(int)
		{
			multiset_iterator tmp(*this);
			--this->it;
			return (tmp);
		}

	private:
		ft::vector_iterator<T>		it;

	}; /** end of class */

	template<typename TL, typename ptrL, typename refL, typename TR, typename ptrR, typename refR>
	bool operator==(const multiset_iterator<TL, ptrL, refL> &lhs, const multiset_iterator<TR, ptrR, refR> &rhs)
	{
		return lhs.getIt() == rhs.getIt();
	}

	template<typename TL, typename ptrL, typename refL, typename TR, typename ptrR, typename refR>
	bool operator!=(const multiset_iterator<TL, ptrL, refL> &lhs, const multiset_iterator<TR, ptrR, refR> &rhs)
	{
		return !(lhs.getIt() == rhs.getIt());
	}
}