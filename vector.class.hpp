#pragma once

# include <cstring>
# include <exception>

# include <string>
# include <memory>
# include <cstddef>
# include <algorithm>


namespace ft {

	template<bool B, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T>
	{ typedef T type; };

// =========================================================================
// --------------------------- VECTOR_ITERATOR -----------------------------
// =========================================================================
	template <typename T, typename Pointer = T*, typename  Reference = T&>
	class vector_iterator
	{

	public:
		typedef std::random_access_iterator_tag			iterator_category;
		typedef T										value_type;
		typedef Pointer									pointer;
		typedef Reference								reference;
		typedef ptrdiff_t								difference_type;
		typedef size_t									size_type;
		typedef vector_iterator<T, Pointer, Reference>	iter_type;
		typedef vector_iterator<T, T*, T&>				iterator;
		typedef vector_iterator<T, const T*, const T&>	const_iterator;

		// =================== CONSTRUCTORS / DESTRUCTOR =======================
		vector_iterator() : current_(0)
		{}

		vector_iterator(const pointer elem)
			: current_(elem)
		{}

		vector_iterator(vector_iterator<T, T *, T &> copy)
				: current_(const_cast<pointer>(copy.base()))
		{}

		~vector_iterator() {}
		// MY
		pointer base() const
		{
			return (this->current_);
		}
		// Operators ===========================================================

		// '='
		iter_type &operator=(vector_iterator<T, T *, T &> const &a)
		{
			if (this == &a)
				return (*this);
			this->current_ = a.current_;
			return (*this);
		}
		// '*'
		reference operator*() const
		{
			return (*this->current_);
		}

		// '->'
		pointer operator->()
		{
			return (*&this->current_);
		}

		// '++ pre'
		iter_type &operator++()
		{
			++this->current_;
			return (*this);
		}

		// '++ post'
		iter_type operator++(int)
		{
			iter_type tmp(*this);
			this->current_++;
			return (tmp);
		}

		// '-- pre'
		iter_type &operator--()
		{
			--this->current_;
			return (*this);
		}

		// '-- post'
		iter_type operator--(int)
		{
			iter_type tmp(*this);
			this->current_--;
			return (tmp);
		}

		// '+'
		iter_type operator+(difference_type const &a) const
		{
			iter_type tmp(*this);
			return (tmp += a);
		}

		// '-'
		iter_type operator-(difference_type const &a) const
		{
			iter_type tmp(*this);
			return (tmp -= a);
		}

		// '-' 2 iters
		difference_type operator-(iter_type const &other)
		{
			return (this->current_ - other.current_);
		}

		// '+='
		iter_type &operator+=(difference_type const &a)
		{
			this->current_ += a;
			return (*this);
		}

		// '-='
		iter_type &operator-=(difference_type const &a)
		{
			this->current_ -= a;
			return (*this);
		}

		// '[]'
		reference operator[](difference_type index)
		{
			return (*(this->current_ + index));
		}
	private:
		pointer current_;
	};

	template<typename TL, typename ptrL, typename refL, typename  TR, typename ptrR, typename refR>
	bool operator== (const vector_iterator<TL, ptrL, refL> &lhs, const vector_iterator<TR, ptrR, refR> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template<typename TL, typename ptrL, typename refL, typename  TR, typename ptrR, typename refR>
	bool operator!= (const vector_iterator<TL, ptrL, refL> &lhs, const vector_iterator<TR, ptrR, refR> &rhs)
	{
		return !(lhs.base() == rhs.base());
	}

	template<typename TL, typename ptrL, typename refL, typename  TR, typename ptrR, typename refR>
	bool operator< (const vector_iterator<TL, ptrL, refL> &lhs, const vector_iterator<TR, ptrR, refR> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template<typename TL, typename ptrL, typename refL, typename  TR, typename ptrR, typename refR>
	bool operator> (const vector_iterator<TL, ptrL, refL> &lhs, const vector_iterator<TR, ptrR, refR> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template<typename TL, typename ptrL, typename refL, typename  TR, typename ptrR, typename refR>
	bool operator>= (const vector_iterator<TL, ptrL, refL> &lhs, const vector_iterator<TR, ptrR, refR> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template<typename TL, typename ptrL, typename refL, typename  TR, typename ptrR, typename refR>
	bool operator<= (const vector_iterator<TL, ptrL, refL> &lhs, const vector_iterator<TR, ptrR, refR> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <typename Iterator>
	ptrdiff_t distance(Iterator first, Iterator last) {
		ptrdiff_t dist = 0;
		while (first != last) {
			++dist;
			++first;
		}
		return dist;
	}

	// =========================================================================
	// ------------------------------- VECTOR ----------------------------------
	// =========================================================================

	template<class T>
	class vector
	{
	public:
// Typedefs ============================================================

		typedef T                                         value_type;
		typedef size_t                                    size_type;
		typedef T*                                        pointer;
		typedef const T*                                  const_pointer;
		typedef T&                                        reference;
		typedef const T&                                  const_reference;
		typedef vector_iterator<T, T*, T&>                iterator;
		typedef vector_iterator<T, const T*, const T&>    const_iterator;
		typedef std::reverse_iterator<iterator>  		  reverse_iterator;
		typedef std::reverse_iterator<const_iterator>     const_reverse_iterator;
// ===================== CONSTRUCTORS / DESTRUCTOR =====================
		explicit vector()
				: array_(0), size_(0), capacity_(0) {}

		explicit vector(size_type n, const value_type &val = value_type())
				: array_(0), size_(0), capacity_(0)
		{
			if (n == 0)
				return;
			try {
				this->array_ = new value_type[n];
				insert(this->begin(), n, val);
			}
			catch (std::exception &e) {
				throw VectorException();
			}
		}
		template<class InputIterator>
		vector(InputIterator first, InputIterator last,
		 typename enable_if< !std::numeric_limits<InputIterator>::is_specialized >::type* = 0)
				: array_(0), size_(0), capacity_(0)
		{
			this->capacity_ = ft::distance(first, last);
			this->array_ = new value_type[this->capacity_];
			for (; first != last; first++)
				push_back(*first);
		}

		explicit vector(const vector &x)
			: array_(0), size_(0), capacity_(0)
		{
			*this = x;
		}

		~vector()
		{
			if (this->array_ != 0)
				delete[] this->array_;
		}

		// ITERATORS ===============================================================

		iterator       begin() {
			return (iterator(this->array_));
		}

		const_iterator begin() const {
			return (const_iterator(this->array_));
		}

		reverse_iterator   rbegin() {
			return (reverse_iterator(this->end()));
		}

		const_reverse_iterator rbegin() const {
			return (reverse_iterator(this->end()));
		}

		iterator end()
		{
			return (iterator(this->array_ + this->size_));
		}

		const_iterator end() const {
			return (const_iterator(this->array_ + this->size_));
		}

		reverse_iterator rend() {
			return (reverse_iterator(this->begin()));
		}

		const_reverse_iterator rend() const {
			return (reverse_iterator(this->begin()));
		}
		// ======================== OPERATORS =================================


		// '='
		vector &operator=(vector const &other) {
			if (this == &other)
				return (*this);

			delete[] this->array_;
			try {
				this->array_ = new T[other.size()];
			}
			catch (std::exception &e) {
				throw VectorException();
			}

			for (size_type i = 0; i < other.size_; ++i) {
				this->array_[i] = other.array_[i];
			}
			this->size_ = other.size_;
			this->capacity_ = other.capacity_;
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


		// Member functions ====================================================

		// Element access ------------------------------------------------------

		reference at(size_type pos) {
			if (pos >= this->size_)
				throw VectorException();
			return (this->array_[pos]);
		}

		const_reference at(size_type pos) const {
			if (pos >= this->size_)
				throw VectorException();
			return (this->array_[pos]);
		}

		reference front() {
			return (this->array_[0]);
		}

		const_reference front() const {
			return (this->array_[0]);
		}

		reference back() {
			return (this->array_[this->size_ - 1]);
		}

		const_reference back() const {
			return (this->array_[this->size_ - 1]);
		}
		// ---------------------------------------------------------------------

		// Capasity ------------------------------------------------------------

		bool empty() const{
			return (!(this->size_));
		}

		size_type size() const {
			return (this->size_);
		}

		size_type max_size() const {
			std::allocator<T> allocator;
			return (allocator.max_size());
		}

		void resize (size_type n, value_type val = value_type()) {
			while (this->size_ > n)
				this->size_--;
			if (n > this->capacity_)
				reserve(n);
			while (n > this->size_)
				push_back(val);
		}

		void reserve(size_type new_cap) {
			if (new_cap <= this->capacity_)
				return;

			try {
				pointer new_array = new T[new_cap];

				size_type i;
				for (i = 0; i < this->size_; ++i)
				{
					new_array[i] = this->array_[i];
				}
				if (this->array_ != 0)
					delete[] this->array_;

				this->array_ = new_array;
				this->capacity_ = new_cap;
			}
			catch (std::exception &e) {
				throw VectorException();
			}
		}

		size_type capacity() const {
			return (this->capacity_);
		}
		// ---------------------------------------------------------------------

		//  Modifiers ----------------------------------------------------------

		// Insert --------------------------------------------------------------
		void insert(iterator position, size_type n, const value_type &val)
		{
			if (n == 0)
				return;
			vector cuted_part(position, this->end());
			iterator it(cuted_part.begin());

			this->size_ -= ft::distance(position, this->end());
			for (size_t i = 0; i < n; i++)
				this->push_back(val);
			for (; it != cuted_part.end(); it++)
				this->push_back(*it);
		}

		iterator insert(iterator position, const value_type &val) {
			size_type save_index = ft::distance(this->begin(), position);
			insert(position, static_cast<size_type>(1), val);
			return iterator(&this->array_[save_index]);
		}

		template<class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last,
					typename enable_if< !std::numeric_limits<InputIterator>::is_specialized >::type* = 0) {
			while (first != last) {
				position = this->insert(position, *first);
				first++;
				position++;
			}
		}

		//Clear ----------------------------------------------------------------
		void clear() {
			this->size_ = 0;
		}

		//Clear ----------------------------------------------------------------
		template<class InputIterator>
		void assign(InputIterator first, InputIterator last,
					typename enable_if< !std::numeric_limits<InputIterator>::is_specialized >::type* = 0) {
			this->clear();
			this->insert(this->begin(), first, last);
		}

		void assign(size_type n, const value_type &val) {
			this->clear();
			this->insert(this->begin(), n, val);
		}

		// Pushback ------------------------------------------------------------
		void push_back(const value_type &val) {
			if (this->size_ == this->capacity_)
				reserve(this->size_ == 0 ? 1 : this->capacity_ * 2);
			this->array_[this->size_] = val;
			this->size_++;
		}

		// Popback -------------------------------------------------------------
		void pop_back() {
			this->size_--;
		}

		// Erase ---------------------------------------------------------------
		iterator erase(iterator position) {
			size_type save_ind = static_cast<size_type>(position - this->begin());

			for (; save_ind < this->size_ - 1; save_ind++)
				this->array_[save_ind] = this->array_[save_ind + 1];
			this->size_--;
			return (position);
		}

		iterator erase(iterator first, iterator last) {
			size_type save = ft::distance(first, last);
			std::copy(last, this->end(), first);
			this->size_ -= save;
			return (first);
		}

		// SWAP
		void swap(vector &x) {
			std::swap(this->array_, x.array_);
			std::swap(this->size_, x.size_);
			std::swap(this->capacity_, x.capacity_);
		}
		// Exceptions ==========================================================

		class VectorException : public std::exception {
			const char *what() const throw() {
				return ("vector");
			}
		};

	private:
		pointer array_;
		size_type size_;
		size_type capacity_;
	};

	template<class InputIterator1, class InputIterator2>
	bool equalx(InputIterator1 first1, InputIterator1 last1,
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
