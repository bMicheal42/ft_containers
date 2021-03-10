#pragma once

#include <list>
#include "utils.hpp"

namespace ft {

	template < class T >
	struct  Node {
		T			data;
		Node		*next;
		Node		*prev;

		Node(const T &val = T())
			: data(val)
		{
			this->next = this;
			this->prev = this;
		}

		Node(const Node<T> *copy)
			: data(copy->data) {}

		~Node() {}
	};

// =============================================================================
// ------------------------------ LIST CLASS ----------------------------------
// =============================================================================

	template < class T, class Alloc = std::allocator<T> >
	class list
	{

	public:

		typedef T                                         value_type;
		typedef T*                                        pointer;
		typedef const T*                                  const_pointer;
		typedef T&                                        reference;
		typedef const T&                                  const_reference;
		typedef vector_iterator<T, T*, T&>                iterator;
		typedef vector_iterator<T, const T*, const T&>    const_iterator;
		typedef std::reverse_iterator<iterator>  		  reverse_iterator;
		typedef std::reverse_iterator<const_iterator>     const_reverse_iterator;
		typedef size_t                                    size_type;
		typedef ptrdiff_t								  difference_type;
		typedef Alloc									  allocator_type;
		typedef Node<T>								      node;

//1
		explicit	list (const allocator_type& alloc = allocator_type())
					: size_(0), alloc_(alloc)
			{
				this->last_ = new node();
			}
//2
		explicit	list (size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type())
					: size_(0), alloc_(alloc)
		{
			this->last_ = new node();
		//	while (this->size_ < n)
		//	push_back(val);
		}
//3
		template <class InputIterator>
		list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
			typename ft::enable_if< !std::numeric_limits<InputIterator>::is_specialized >::type* = 0)
			: size_(0), alloc_(alloc)
		{
			this->last_ = new node();
		//	for (; first != last; ++first)
		//	push_back(*first);
		}
//4
		list (const list& x)
			:size_(x.size_), alloc_(x.alloc_)
		{
			this->last_ = new node();
			//insert в конец от начала до конца следующего
		}
//5
		~list()
		{
			//erase begin -end or While size > 0 pop
			//delete
		}

//6
		long &operator=(const list &src) {
			if (*this == src)
				return *this;
//			assign(src.begin(), src.end());
			return *this;
		}
// ================================== ITERATORS ================================

// =============================== MEMBER FUNCTIONS ===========================
		bool			empty() const { return (this->size_ == 0); }
		size_type		size() const { return (this->size_); }
		size_type		max_size() const { return (std::numeric_limits<size_type>::max() / sizeof(node)); }


	private:
		size_type			size_;
		allocator_type		alloc_;
		node*				last_;

}; //end of class LIST
}