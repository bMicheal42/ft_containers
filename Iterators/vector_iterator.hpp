#pragma once

namespace ft {

// =============================================================================
 /** ---------------------------- VECTOR_ITERATOR --------------------------- */
// =============================================================================
	template<typename T, typename Pointer = T*, typename Reference = T&>
	class vector_iterator
	{

	public:
		typedef std::random_access_iterator_tag				iterator_category;
		typedef T											value_type;
		typedef Pointer										pointer;
		typedef Reference									reference;
		typedef ptrdiff_t									difference_type;
		typedef size_t										size_type;

// ====================== CONSTRUCTORS / DESTRUCTOR ============================
		vector_iterator() :current_(0) {}

		vector_iterator(pointer elem) :current_(elem) {}

		vector_iterator(vector_iterator<T, T*, T&> const &copy) :current_(copy.base()) {}

		~vector_iterator() {}

		pointer base() const { return (this->current_); }
// ============================ OPERATORS ======================================

		// '='
		vector_iterator		&operator=(vector_iterator const &other)
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
		vector_iterator 	&operator++()
		{
			++this->current_;
			return (*this);
		}

		// '++ post'
		vector_iterator		operator++(int)
		{
			vector_iterator tmp(*this);
			this->current_++;
			return (tmp);
		}

		// '-- pre'
		vector_iterator		&operator--()
		{
			--this->current_;
			return (*this);
		}

		// '-- post'
		vector_iterator		operator--(int)
		{
			vector_iterator tmp(*this);
			this->current_--;
			return (tmp);
		}

		// '+'
		vector_iterator		operator+(difference_type const &a) const
		{
			vector_iterator tmp(*this);
			return (tmp += a);
		}

		// '-'
		vector_iterator		operator-(difference_type const &a) const
		{
			vector_iterator tmp(*this);
			return (tmp -= a);
		}

		// '-' 2 iters
		difference_type		operator-(vector_iterator const &other)
		{
			return (this->current_ - other.current_);
		}

		// '+='
		vector_iterator		&operator+=(difference_type const &a)
		{
			this->current_ += a;
			return (*this);
		}

		// '-='
		vector_iterator		&operator-=(difference_type const &a)
		{
			this->current_ -= a;
			return (*this);
		}

		// '[]'
		reference			operator[](difference_type index) { return (*(this->current_ + index)); }

	private:
		pointer current_;

	}; /** end of class */
	template<typename TL, typename ptrL, typename refL, typename TR, typename ptrR, typename refR>
	bool operator==(const vector_iterator<TL, ptrL, refL> &lhs, const vector_iterator<TR, ptrR, refR> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template<typename TL, typename ptrL, typename refL, typename TR, typename ptrR, typename refR>
	bool operator!=(const vector_iterator<TL, ptrL, refL> &lhs, const vector_iterator<TR, ptrR, refR> &rhs)
	{
		return !(lhs.base() == rhs.base());
	}

	template<typename TL, typename ptrL, typename refL, typename TR, typename ptrR, typename refR>
	bool operator<(const vector_iterator<TL, ptrL, refL> &lhs, const vector_iterator<TR, ptrR, refR> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template<typename TL, typename ptrL, typename refL, typename TR, typename ptrR, typename refR>
	bool operator>(const vector_iterator<TL, ptrL, refL> &lhs, const vector_iterator<TR, ptrR, refR> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template<typename TL, typename ptrL, typename refL, typename TR, typename ptrR, typename refR>
	bool operator>=(const vector_iterator<TL, ptrL, refL> &lhs, const vector_iterator<TR, ptrR, refR> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template<typename TL, typename ptrL, typename refL, typename TR, typename ptrR, typename refR>
	bool operator<=(const vector_iterator<TL, ptrL, refL> &lhs, const vector_iterator<TR, ptrR, refR> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

}