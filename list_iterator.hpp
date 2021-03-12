#include "list.class.hpp"

namespace ft {

// =========================================================================
// --------------------------- LIST_ITERATOR -----------------------------
// =========================================================================
	template<typename T, typename Pointer = T *, typename Reference = T &>
	class list_iterator
	{
		typedef Node<T>

	public:
		typedef list_iterator<T, T *, T &>				iterator;
		typedef std::bidirectional_iterator_tag			iterator_category;
		typedef T 										value_type;
		typedef Pointer									pointer;
		typedef Reference								reference;
		typedef ptrdiff_t								difference_type;
		typedef size_t									size_type;
		typedef list_iterator<T, Pointer, Reference>	iter_type;
		typedef list_iterator<T, const T *, const T &>	const_iterator;
//
//		// =================== CONSTRUCTORS / DESTRUCTOR =======================
//		vector_iterator() : current_(0) {}
//
//		vector_iterator(const pointer elem)
//				: current_(elem) {}
//
//		vector_iterator(vector_iterator<T, T *, T &> copy)
//				: current_(const_cast<pointer>(copy.base())) {}
//
//		~vector_iterator() {}
//		// MY
//		pointer base() const
//		{
//			return (this->current_);
//		}
//		// Operators ===========================================================
//
//		// '='
//		iter_type &operator=(vector_iterator<T, T *, T &> const &a)
//		{
//			if (this == &a)
//				return (*this);
//			this->current_ = a.current_;
//			return (*this);
//		}
//		// '*'
//		reference operator*() const
//		{
//			return (*this->current_);
//		}
//
//		// '->'
//		pointer operator->()
//		{
//			return (*&this->current_);
//		}
//
//		// '++ pre'
//		iter_type &operator++()
//		{
//			++this->current_;
//			return (*this);
//		}
//
//		// '++ post'
//		iter_type operator++(int)
//		{
//			iter_type tmp(*this);
//			this->current_++;
//			return (tmp);
//		}
//
//		// '-- pre'
//		iter_type &operator--()
//		{
//			--this->current_;
//			return (*this);
//		}
//
//		// '-- post'
//		iter_type operator--(int)
//		{
//			iter_type tmp(*this);
//			this->current_--;
//			return (tmp);
//		}
//
//		// '+'
//		iter_type operator+(difference_type const &a) const
//		{
//			iter_type tmp(*this);
//			return (tmp += a);
//		}
//
//		// '-'
//		iter_type operator-(difference_type const &a) const
//		{
//			iter_type tmp(*this);
//			return (tmp -= a);
//		}
//
//		// '-' 2 iters
//		difference_type operator-(iter_type const &other)
//		{
//			return (this->current_ - other.current_);
//		}
//
//		// '+='
//		iter_type &operator+=(difference_type const &a)
//		{
//			this->current_ += a;
//			return (*this);
//		}
//
//		// '-='
//		iter_type &operator-=(difference_type const &a)
//		{
//			this->current_ -= a;
//			return (*this);
//		}
//
//		// '[]'
//		reference operator[](difference_type index)
//		{
//			return (*(this->current_ + index));
//		}
	private:
		pointer current_;
	};
}