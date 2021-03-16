#pragma once

#define	fl std
#include <list>
#include "../utils.hpp"
#include "../Iterators/list_iterator.hpp"
#include <iostream> //

namespace ft {

// =============================================================================
/** ------------------------------ LIST CLASS ---------------------------------*/
// =============================================================================

	template < class T, class Alloc = std::allocator<T> >
	class list
	{
// ============================ NODE STRUCT ====================================
		struct  Node
		{
			T data;
			Node *next;
			Node *prev;

			Node (const T &val = T()) :data(val) {
				this->prev	=	this;
				this->next	=	this;
			}
			Node (const Node *copy) :data(copy->data) {}
			~Node () {}
		};
// =============================================================================
	public:

		typedef T                                               value_type;
		typedef Alloc								            allocator_type;
		typedef size_t                                          size_type;
		typedef T*                                              pointer;
		typedef const T*                             			const_pointer;
		typedef T&                                      		reference;
		typedef const T&                                  		const_reference;
		typedef list_iterator<T, Node, T*, T&>   			    iterator;
		typedef list_iterator<T, Node, const T*, const T&> 	    const_iterator;
		typedef fl::reverse_iterator<iterator>  		        reverse_iterator;
		typedef fl::reverse_iterator<const_iterator>            const_reverse_iterator;
		typedef ptrdiff_t								        difference_type;
		typedef Node								            node;

	private:
		size_type			size_;
		allocator_type		alloc_;
		node*				last_;

//======================= CONSTRUCTORS / DESTRUCTORS ===========================
	public:
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
			while (n--)
				push_back(val);
		}
//3
		template <class InputIterator>
		list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
			typename ft::enable_if< !std::numeric_limits<InputIterator>::is_specialized >::type* = 0)
			: size_(0), alloc_(alloc)
		{
			this->last_ = new node();
			for (; first != last; ++first)
				push_back(*first);
		}
//4
		list (const list &x)
			:size_(0), alloc_(x.alloc_)
		{
			this->last_ = new node();
			for(const_iterator it = x.begin(); it != x.end(); ++it)
				push_back(*it);
		}
//5
		~list()
		{
			while (size_ > 0)
				pop_back();
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

		// --------------------------- ASSIGN ----------------------------------
		template <class InputIterator>
		void		assign(InputIterator first, InputIterator last,
					typename ft::enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = 0) {
			ft::list<T> tmp_list(first, last);
			this->clear();
			insert(this->begin(), tmp_list.begin(), tmp_list.end());
		}

		void		assign(size_type n, const value_type& val) {
			value_type tmp_val = val;
			this->clear();
			while (this->size_ < n)
				this->push_back(tmp_val);
		}

		// --------------------------- PUSH FRONT ------------------------------
		void		push_front (const value_type& val)	{ insert_node(last_, last_->next, val); }

		// --------------------------- POP FRONT -------------------------------
		void		pop_front()							{ delete_node(last_->next); }

		// --------------------------- PUSH BACK--------------------------------
		void		push_back (const value_type &val)	{ insert_node(last_->prev, last_, val); }

		// --------------------------- POP BACK --------------------------------
		void		pop_back()							{ delete_node(last_->prev); }

		// ---------------------------- INSERT ---------------------------------
		iterator	insert (iterator position, const value_type& val)
		{
			insert_node(position.getNode()->prev, position.getNode(), val);
			return (--position);
		}

		void 		insert (iterator position, size_type n, const value_type& val)
		{
			while (n-- > 0)
				position = insert(position, val);
		}


		template <class InputIterator>
		void		insert (iterator position, InputIterator first, InputIterator last,
							typename ft::enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = 0)
		{
			last_->data = this->size();
			ft::list<T> tmp_list(first, last);

//			std::cout << "tmp_list: ";
//			for (ft::list<int>::iterator iter(tmp_list.begin()); iter != tmp_list.end(); iter++)
//				std::cout << *iter << " ";
//			std::cout << std::endl;
//
			iterator it1 = tmp_list.begin();
			iterator it2 = --tmp_list.end();

//			std::cout << "iters: " << *it1 << " " << *it2 << std::endl;

			for (; it1 != it2; ++it1)
				insert(position, *it1);
			insert(position, *it1);
		}

		// --------------------------- ERASE -----------------------------------
		iterator	erase(iterator position)
		{
			iterator save_it(position.getNode()->next);
			delete_node(position.getNode());
			return (save_it);
		}

		iterator	erase(iterator first, iterator last)
		{
			for (; first != last; first++)
				delete_node((first.getNode()));
			return (last);
		}

		// ------------------------- RESIZE ------------------------------------
		void		resize (size_type n, value_type val = value_type())
		{
			value_type tmp_val(val);
			while (n < this->size_)
				pop_back();
			while (n > this->size_)
				push_back(tmp_val);
		}

		// ---------------------------- CLEAR ----------------------------------
		void		clear() {
			while (this->size_)
				pop_back();
		}

//==============================================================================

		void		insert_node(node *const prev_node, node *const next_node, value_type val)
		{
			node *new_node	= new node(val);
			new_node->next	= next_node;
			new_node->prev	= prev_node;
			prev_node->next	= new_node;
			next_node->prev = new_node;
			this->size_++;
		}

		void		delete_node(node *to_delete)
		{
//			if (!this->size_)
//				return;
			to_delete->next->prev = to_delete->prev;
			to_delete->prev->next = to_delete->next;
			delete to_delete;
			this->size_--;
		}

		void		swap(list& x)
		{
			fl::swap(size_, x.size_);
			fl::swap(alloc_, x.alloc_);
			fl::swap(last_, x.last_);
		}
	}; /** end of class LIST */

	template<class T, typename Node>
	bool operator==(const ft::vector<T, Node> &lhs, const ft::vector<T, Node> &rhs) {
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equalx(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<class T, typename Node>
	bool operator!=(const ft::vector<T, Node> &lhs, const ft::vector<T, Node> &rhs) {
		return (!(lhs == rhs));
	}

	template<class T, typename Node>
	bool operator<(const ft::vector<T, Node> &lhs, const ft::vector<T, Node> &rhs) {
		return (fl::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<class T, typename Node>
	bool operator>(const ft::vector<T, Node> &lhs, const ft::vector<T, Node> &rhs) {
		return (fl::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	}

	template<class T, typename Node>
	bool operator>=(const ft::vector<T, Node> &lhs, const ft::vector<T, Node> &rhs) {
		return (!(lhs < rhs));
	}

	template<class T, typename Node>
	bool operator<=(const ft::vector<T, Node> &lhs, const ft::vector<T, Node> &rhs) {
		return (!(lhs > rhs));
	}
} /** end of namespace */