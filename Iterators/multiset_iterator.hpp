#pragma once

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
		multiset_iterator() :current_(0) {}

		multiset_iterator(pointer elem) :current_(elem) {}

		multiset_iterator(multiset_iterator<T, T*, T&> const &copy) :current_(copy.base()) {}

		~multiset_iterator() {}

		pointer base() const { return (this->current_); }
// ============================ OPERATORS ======================================

		// '='
		multiset_iterator		&operator=(multiset_iterator const &other)
		{
			if (&other != this)
				current_ = other.current_;
			return (*this);
		}

		// '*'
		reference			operator*() const { return (*this->current_); }

		// '->'
		pointer				operator->() { return (*&this->current_); }

		// '++ pre'
		multiset_iterator 	&operator++()
		{
			++this->current_;
			return (*this);
		}

		// '++ post'
		multiset_iterator		operator++(int)
		{
			multiset_iterator tmp(*this);
			this->current_++;
			return (tmp);
		}

		// '-- pre'
		multiset_iterator		&operator--()
		{
			--this->current_;
			return (*this);
		}

		// '-- post'
		multiset_iterator		operator--(int)
		{
			multiset_iterator tmp(*this);
			this->current_--;
			return (tmp);
		}

	private:
		pointer current_;

	}; /** end of class */

	template<typename TL, typename ptrL, typename refL, typename TR, typename ptrR, typename refR>
	bool operator==(const multiset_iterator<TL, ptrL, refL> &lhs, const multiset_iterator<TR, ptrR, refR> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template<typename TL, typename ptrL, typename refL, typename TR, typename ptrR, typename refR>
	bool operator!=(const multiset_iterator<TL, ptrL, refL> &lhs, const multiset_iterator<TR, ptrR, refR> &rhs)
	{
		return !(lhs.base() == rhs.base());
	}
}