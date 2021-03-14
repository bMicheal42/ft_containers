#pragma once

#include <list>
#include "../utils.hpp"
#include "../Iterators/list_iterator.hpp"

namespace ft {

	template <class T>
	struct  Node {
		T			data;
		Node		*next;
		Node		*prev;

		Node(const T &val = T())
			:data(val)
		{
			this->next = this;
			this->prev = this;
		}

		Node(const Node<T> *copy)
			:data(copy->data) {}

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
		typedef Alloc									  allocator_type;
		typedef size_t                                    size_type;
		typedef T*                                        pointer;
		typedef const T*                                  const_pointer;
		typedef T&                                        reference;
		typedef const T&                                  const_reference;
		typedef list_iterator<T, T*, T&>                  iterator;
		typedef list_iterator<T, const T*, const T&>   	  const_iterator;
		typedef std::reverse_iterator<iterator>  		  reverse_iterator;
		typedef std::reverse_iterator<const_iterator>     const_reverse_iterator;
		typedef ptrdiff_t								  difference_type;
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
		list &operator=(const list &other) {
			list ez(other);
			swap(ez);
			return (*this);
		}
// ================================== ITERATORS ================================

		iterator       			begin()				{ return (size_ == 0 ? iterator(last_) : iterator(last_->next)); }
		const_iterator 			begin() const		{ return (size_ == 0 ? const_iterator(last_) : const_iterator(last_->next)); }
		reverse_iterator   		rbegin()			{ return (size_ == 0 ? reverse_iterator(last_) : reverse_iterator(last_->prev)); }
		const_reverse_iterator 	rbegin() const		{ return (size_ == 0 ? const_reverse_iterator(last_) : const_reverse_iterator(last_->prev)); }
		iterator				end()				{ return (iterator(last_)); }
		const_iterator			end() const 		{ return (const_iterator(last_)); }
		reverse_iterator		rend()				{ return (reverse_iterator(last_)); }
		const_reverse_iterator	rend() const		{ return (const_reverse_iterator(last_)); }

// =============================== MEMBER FUNCTIONS ===========================

		bool					empty() const 		{ return (this->size_ == 0); }
		size_type				size() const 		{ return (this->size_); }
		size_type				max_size() const	{ return (std::numeric_limits<size_type>::max() / sizeof(node)); }

//================================= ELEMENT ACCESS =============================

		reference				front()				{ return (last_->next->data); }
		const_reference			front() const		{ return (last_->next->data); }
		reference				back()				{ return (last_->prev->data); }
		const_reference			back() const		{ return (last_->prev->data); }

//=================================== MODIFIERS ================================

//		template <class InputIterator>
//		void assign(InputIterator first, InputIterator last) {
//			for(; first != last; first++)
//				assign(1, *first);
//		}
//
//		void assign(size_type n, const value_type& val) {
//
//		}

		void push_front (const value_type& val)
		{
			node new_node(val);
			insert_node(last_, last_->next, new_node);
		}

		void pop_front() { delete_node(last_->next); }

		void push_back (const value_type &val)
		{
			node new_node(val);
			insert_node(last_->prev, last_, new_node);
		}

		void pop_back() { delete_node(last_->prev); }

//		iterator insert (iterator position, const value_type& val);

//		void insert (iterator position, size_type n, const value_type& val);

//		template <class InputIterator>
//		void insert (iterator position, InputIterator first, InputIterator last);

		iterator erase (iterator position)
		{
			iterator save_it(position.getNode()->next);
			delete_node(position.getNode());
			return (save_it);
		}

		iterator erase (iterator first, iterator last)
		{
			iterator save_it(last.getNode()->next);
			for (; first != last; first++)
				delete_node((first.getNode()));
			return (save_it);
		}
//==============================================================================

		void			insert_node(node *const prev_node, node *const next_node, node *const new_node)
		{
			new_node->next	= next_node;
			new_node->prev	= prev_node;
			prev_node->next	= new_node;
			next_node->prev = new_node;
			this->size_++;
		}

		void			delete_node(node *to_delete)
		{
			to_delete->next->prev = to_delete->next;
			to_delete->prev->next = to_delete->prev;
			delete to_delete;
			this->size_--;
		}

		void			swap(list& x)
		{
			std::swap(size_, x.size_);
			std::swap(alloc_, x.alloc_);
			std::swap(last_, x.last_);
		}

	private:
		size_type			size_;
		allocator_type		alloc_;
		node*				last_;

	}; //end of class LIST
}