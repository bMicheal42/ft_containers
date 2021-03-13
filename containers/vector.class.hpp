#pragma once

# include <cstring>
# include <exception>
# include <string>
# include <memory>
# include <cstddef>
# include <algorithm>

# include "../Iterators/vector_iterator.hpp"
# include "../utils.hpp"

namespace ft {

	template <typename Iterator>
	ptrdiff_t distance(Iterator first, Iterator last) {
		ptrdiff_t dist = 0;
		if (first == last)
			return 0;
		while (first != last) {
			++dist;
			++first;
		}
		return dist;
	}

	// =========================================================================
	// ------------------------------- VECTOR ----------------------------------
	// =========================================================================

	template<class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:

		typedef T                                         value_type;
		typedef Alloc								      allocator_type;
		typedef size_t                                    size_type;
		typedef T*                                        pointer;
		typedef const T*                                  const_pointer;
		typedef T&                                        reference;
		typedef const T&                                  const_reference;
		typedef vector_iterator<T, T*, T&>                iterator;
		typedef vector_iterator<T, const T*, const T&>    const_iterator;
		typedef std::reverse_iterator<iterator>  		  reverse_iterator;
		typedef std::reverse_iterator<const_iterator>     const_reverse_iterator;


		explicit	vector(const allocator_type &alloc = allocator_type())
			: alloc_(alloc), size_(0), capacity_(0), array_(0)
		{
			array_ = alloc_.allocate(this->capacity_);
		}


		explicit	vector(size_type n, const value_type &val = value_type(),
				  const allocator_type& alloc = allocator_type())
					: alloc_(alloc), size_(n), capacity_(n), array_(0)
		{
			if (n == 0)
				return;
			array_ = alloc_.allocate(this->capacity_);
			for (size_type i = 0; i < this->size_; i++)
				alloc_.construct(array_ + i, val);

		}


		template<class InputIterator>
		vector(InputIterator first, InputIterator last,
		 typename ft::enable_if< !std::numeric_limits<InputIterator>::is_specialized >::type* = 0, const allocator_type& alloc = allocator_type())
				: alloc_(alloc), array_(0), capacity_(0)
		{
			this->size_			= ft::distance(first, last);
			this->capacity_ 	= this->size_;
				array_ = alloc_.allocate(this->capacity_);
			for (size_type i = 0; first != last; ++i, ++first)
				alloc_.construct(array_ + i, *first);
		}


		vector(const vector &x) : alloc_(x.alloc_), size_(x.size_), capacity_(x.capacity_)
		{
			array_ = alloc_.allocate(this->capacity_);
			this->alloc_		= x.alloc_;
			this->size_			= x.size_;
			this->capacity_		= x.capacity_;
			for (size_type i = 0; i < this->size_; ++i)
				alloc_.construct(this->array_ + i, x[i]);
		}


		~vector() {
			for (iterator it = this->begin(); it != this->end(); ++it)
				alloc_.destroy(&(*it));
			alloc_.deallocate(this->array_, this->capacity_);
		}

		// ITERATORS ===============================================================

		iterator       			begin()			{ return (iterator(this->array_)); }

		const_iterator 			begin() const	{ return (const_iterator(this->array_)); }

		reverse_iterator   		rbegin()		{ return (reverse_iterator(this->end())); }

		const_reverse_iterator 	rbegin() const	{ return (reverse_iterator(this->end())); }

		iterator				end()			{ return (iterator(this->array_ + this->size_)); }

		const_iterator			end() const 	{ return (const_iterator(this->array_ + this->size_)); }

		reverse_iterator		rend()			{ return (reverse_iterator(this->begin())); }

		const_reverse_iterator	rend() const	{ return (reverse_iterator(this->begin())); }

		// ======================== OPERATORS =================================

		// '='
		vector &operator=(vector const &other) {
			vector ez(other);
			swap (ez);
			return (*this);
		};

		// '[]'
		reference operator[](size_type index) {
			return (this->array_[index]);
		}

		// '[]'
		const_reference operator[](size_type index) const {
			return (this->array_[index]);
		}


		// Element access ------------------------------------------------------

		reference		at(size_type pos) {
			if (pos >= this->size_)
				throw VectorException();
			return (this->array_[pos]);
		}

		const_reference at(size_type pos) const {
			if (pos >= this->size_)
				throw VectorException();
			return (this->array_[pos]);
		}

		reference		front() {
			return (this->array_[0]);
		}

		const_reference	front() const {
			return (this->array_[0]);
		}

		reference		back() {
			return (this->array_[this->size_ - 1]);
		}

		const_reference	back() const {
			return (this->array_[this->size_ - 1]);
		}

		// Capasity ------------------------------------------------------------

		bool		empty() const{
			return (!(this->size_));
		}

		size_type	size() const {
			return (this->size_);
		}

		size_type	max_size() const {
			return (this->alloc_.max_size());
		}

		void		resize (size_type n, value_type val = value_type()) {
			value_type tmp_val(val);
			if (n > this->capacity_)
				my_realloc(n);
			while (n > this->size_)
				push_back(tmp_val);
			while (n < this->size_)
				pop_back();
		}

		void		reserve(size_type new_cap) {
			if (new_cap <= this->capacity_)
				return;
			try {
				if (new_cap > this->max_size())
					throw VectorException();
				if (new_cap > this->capacity_)
					my_realloc(new_cap);
			}
			catch (std::exception &e) {
				throw VectorException();
			}
		}

		size_type	capacity() const {
			return (this->capacity_);
		}


		// Insert --------------------------------------------------------------
		void		insert(iterator position, size_type n, const value_type &val)
		{
			value_type tmp_val(val);
			if (n == 0)
				return;
			size_type start_pos = ft::distance(this->begin(), position);

			if ((this->size_ + n) > this->capacity_)
				my_realloc(this->capacity_ == 0 ? n : this->capacity_ * 2);
			if ((this->size_ + n) > this->capacity_)
				my_realloc(this->capacity_ + n);
			iterator new_start(array_ + start_pos);
			if (new_start != this->end())
			{
				ft::pair<iterator, iterator> it(end() - 1, end());
				for (; it.element2 != new_start; --it.element1, --it.element2)
				{
					alloc_.construct(&(*(it.element1 + n)), *it.element1);
					alloc_.destroy(&(*it.element1));
				}
			}
			this->size_ += n;
			for(; n != 0; n--, start_pos++)
				alloc_.construct(this->array_ + start_pos, tmp_val);
		}

		iterator	insert(iterator position, const value_type &val) {
			size_type save_index = ft::distance(this->begin(), position);
			insert(position, 1, val);
			return iterator(&this->array_[save_index]);
		}

		template<class InputIterator>
		void		insert(iterator position, InputIterator first, InputIterator last,
					typename ft::enable_if< !std::numeric_limits<InputIterator>::is_specialized >::type* = 0) {
			for (; first != last; first++, position++)
				position = this->insert(position, *first);
		}

		// CLEAR ----------------------------------------------------------------
		void		clear() {
			while (this->size_)
				pop_back();
		}

		// ASSIGN ----------------------------------------------------------------
		template<class InputIterator>
		void		assign(InputIterator first, InputIterator last,
					typename ft::enable_if< !std::numeric_limits<InputIterator>::is_specialized >::type* = 0) {
			this->clear();
			this->insert(this->begin(), first, last);
		}

		void		assign(size_type n, const value_type &val) {
			this->clear();
			this->insert(this->begin(), n, val);
		}

		// PUSHBACK ------------------------------------------------------------
		void		push_back(const value_type &val) {
			if (this->size_ == this->capacity_)
				my_realloc(this->capacity_ == 0 ? 1 : this->capacity_ * 2);
			this->alloc_.construct(&array_[this->size_], val);
			this->size_++;
		}

		// POPBACK -------------------------------------------------------------
		void		pop_back() {
			if (this->size_)
			{
				this->alloc_.destroy(&array_[this->size_ - 1]);
				this->size_--;
			}
		}

		// ERASE ---------------------------------------------------------------
		iterator	erase(iterator position) {
			return erase(position, position + 1);
		}

		iterator	erase(iterator first, iterator last) {
			if (first == last || first == this->end())
				return first;
			size_type	start_i		= first - this->begin();
			size_type	tmp_i		= start_i;
			size_type	n			= last - first;

			for (; first != last; first++, start_i++)
				this->alloc_.destroy(&array_[start_i]);
			std::memmove(array_ + tmp_i, array_ + tmp_i + n,  sizeof(value_type) * (this->size_ - tmp_i));
			this->size_ -= n;
			return (iterator(this->array_ + tmp_i));
		}

		// SWAP
		void		swap(vector &x) {
			std::swap(this->alloc_, x.alloc_);
			std::swap(this->array_, x.array_);
			std::swap(this->size_, x.size_);
			std::swap(this->capacity_, x.capacity_);
		}
		// Exceptions ==========================================================

		class		VectorException : public std::exception {
			const char *what() const throw() {
				return ("vector");
			}
		};

	private:

		void		my_realloc(size_type new_cap)
		{
			pointer new_array	= alloc_.allocate(new_cap);
			for (size_type i = 0; i < this->size(); ++i)
				alloc_.construct(new_array + i, this->array_[i]);
			this->~vector();
			this->array_		= new_array;
			this->capacity_ 	= new_cap;
			this->capacity_ 	= new_cap;
		}

		allocator_type 		alloc_;
		pointer				array_;
		size_type			size_;
		size_type			capacity_;
	};

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

	template<class T>
	void swap(ft::vector<T> &x, ft::vector<T> &y) {
		x.swap(y);
	}

	template<class T>
	typename ft::vector_iterator<T> operator+ (typename ft::vector_iterator<T>::difference_type n, typename ft::vector_iterator<T> const &x)
	{
		return (x + n);
	}

	template<class T>
	bool operator==(const ft::vector<T> &lhs, const ft::vector<T> &rhs) {
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equalx(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<class T>
	bool operator!=(const ft::vector<T> &lhs, const ft::vector<T> &rhs) {
		return (!(lhs == rhs));
	}

	template<class T>
	bool operator<(const ft::vector<T> &lhs, const ft::vector<T> &rhs) {
		return (std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<class T>
	bool operator>(const ft::vector<T> &lhs, const ft::vector<T> &rhs) {
		return (std::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	}

	template<class T>
	bool operator>=(const ft::vector<T> &lhs, const ft::vector<T> &rhs) {
		return (!(lhs < rhs));
	}

	template<class T>
	bool operator<=(const ft::vector<T> &lhs, const ft::vector<T> &rhs) {
		return (!(lhs > rhs));
	}
} // end of namespace
