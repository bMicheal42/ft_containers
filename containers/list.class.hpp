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
			delete this->last_;
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
			last_->data = this->size();
			ft::list<T> tmp_list(first, last);
			this->clear();
			insert(this->begin(), tmp_list.begin(), tmp_list.end());
		}

		void		assign(size_type n, const value_type& val) {
			last_->data = this->size();
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
			last_->data = this->size();
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

			iterator it1 = tmp_list.begin();
			iterator it2 = --tmp_list.end();

			for (; it1 != it2; ++it1)
				insert(position, *it1);
			insert(position, *it1);
		}

		// --------------------------- ERASE -----------------------------------
		iterator	erase(iterator position) {
			iterator save_it(position.getNode()->next);
			delete_node(position.getNode());
			return (save_it);
		}

		iterator	erase(iterator first, iterator last) { //STD seg if first > last
			while (first != last)
				first = erase(first);
			return first;
		}

		// ------------------------- RESIZE ------------------------------------
		void		resize (size_type n, value_type val = value_type()) {
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
		// --------------------------- SWAP ------------------------------------
		void		swap(list& x) {
			fl::swap(size_, x.size_);
			fl::swap(alloc_, x.alloc_);
			fl::swap(last_, x.last_);
		}


//============================== OPERATIONS ====================================

		// ----------------------- SPLICE --------------------------------------
		void		splice (iterator position, list &x) {
			while(x.size_)
				splice(position, x, x.begin());
		}

		void		splice (iterator position, list &x, iterator i) {
			node *new_node						= i.getNode();

			i.getNode()->prev->next 			= i.getNode()->next;
			i.getNode()->next->prev 			= i.getNode()->prev;

			new_node->next						= position.getNode();
			new_node->prev						= position.getNode()->prev;
			position.getNode()->prev->next		= new_node;
			position.getNode()->prev			= new_node;

			--x.size_;
			++this->size_;
		}

		void		splice (iterator position, list &x, iterator first, iterator last) {
			if (first == last)
				return;

			iterator new_last(last.getNode()->prev);

			size_type  n  = 0;
			for (iterator tmp(first); tmp != last; ++tmp, ++n);

			first.getNode()->prev->next			= last.getNode();
			last.getNode()->prev				= first.getNode()->prev;

			position.getNode()->prev			= new_last.getNode();
			position.getNode()->prev->next		= first.getNode();

			first.getNode()->prev				= position.getNode()->prev;
			new_last.getNode()->next			= position.getNode();

			x.size_		-= n;
			this->size_ += n;
		}

		// ----------------------- REMOVE --------------------------------------
		void		remove (const value_type &val) {
			value_type tmp_val = val;
			for (iterator tmp(begin()); tmp != this->end(); ++tmp)
				if (tmp.getNode().data == tmp_val)
					delete_node(tmp.getNode());
		}

		template <class Predicate>
		void		remove_if (Predicate pred) {
			for (iterator tmp(begin()); tmp != this->end(); ++tmp)
				if (pred(tmp.getNode().data) == true)
					delete_node(tmp.getNode());
		}
		// ----------------------- UNIQUE --------------------------------------
		void		unique() {
			for (iterator tmp(begin()); tmp != this->end(); ++tmp) /**   NEED A CHECK */
				if (*tmp == tmp.getNode()->next->data)
					delete_node(tmp.getNode()->next);
		}

		template <class BinaryPredicate>
		void		unique (BinaryPredicate binary_pred) {
			for (iterator tmp(begin()); tmp != this->end(); ++tmp) /**   NEED A CHECK */
				if (binary_pred(tmp.getNode()->next->data, tmp.getNode()->next->next->data))
					delete_node(tmp.getNode()->next->next);
		}

		// ----------------------- MERGE --------------------------------------
		void		merge (list &x) {
			if (&x == this)
				return ;

			iterator it1	= this->begin();
			iterator it_x1	= x.begin();

			while (it1 != this->end() && it_x1 != x.end())
			{
				if ((*it_x1) < (*it1))
				{
					++it_x1;
					relink(it1.getNode()->prev, it1.getNode(), it_x1.getNode()->prev);
				}
				else
					++it1;
			}
			if (it_x1 != x.end())
			{
				it_x1.getNode()->prev			= it1.getNode()->prev;
				it1.getNode()->prev->next		= it_x1.getNode();
				x.end().getNode()->prev->next	= last_;
				last_->prev						= x.end().getNode()->prev;
			}
			this->size_		+= x.size_;
			x.size_			= 0;
			x.last_->next	= x.last_;
			x.last_->prev	= x.last_;
		}

		template <class Compare>
		void		merge (list &x, Compare comp) {
			if (&x == this)
				return ;

			iterator it1	= this->begin();
			iterator it_x1	= x.begin();

			while (it1 != this->end() && it_x1 != x.end())
			{
				if (comp(*it_x1, *it1) == true)
				{
					++it_x1;
					relink(it1.getNode()->prev, it1.getNode(), it_x1.getNode()->prev);
				}
				else
					++it1;
			}
			if (it_x1 != x.end())
			{
				it_x1.getNode()->prev			= it1.getNode()->prev;
				it1.getNode()->prev->next		= it_x1.getNode();
				x.end().getNode()->prev->next	= last_;
				last_->prev						= x.end().getNode()->prev;
			}
			this->size_		+= x.size_;
			x.size_			= 0;
			x.last_->next	= x.last_;
			x.last_->prev	= x.last_;
		}

		// ------------------------- SORT --------------------------------------

//		void		sort() {
//			merge_sort(this->begin(), this->end(), ft::my_comp<value_type>);
//		}



//		template <class Compare>
//		void sort (Compare comp) {
//			merge_sort(this->begin(), this->end(), comp);
//		}


		// ----------------------- REVERSE -------------------------------------
		void		reverse()
		{
			node *current = last_;
			node *next		= current->next;
			current->next	= current->prev;
			current->prev	= next;
			current			= next;
			while (current != last_)
			{
				next			= current->next;
				current->next	= current->prev;
				current->prev	= next;
				current			= next;
			}
		}


//================================== MY ========================================
//	private:

		// ------------ STAFF for RECURSIVE MERGE SORT -------------------------
//		bool		my_comp(value_type x, value_type y)
//		{
//			return (x > y);
//		}
//
//		iterator	split_lists(iterator first, iterator last)
//		{
//			iterator fast	= first;
//			iterator slow	= first;
//
//			while (fast.getNode()->next != last.getNode() && fast.getNode()->next->next != last.getNode())
//			{
//				++fast; ++fast;
//				++slow;
//			}
//			return(++slow);
//		}
//
//		template <class Compare>
//		iterator	merge_sorted_lists(iterator first1, iterator last1, iterator first2, iterator last2, Compare comp)
//		{
//			iterator  ret = first1;
//			node *node1;
//			node *node2;
//
//			while (first2 != last2)
//			{
//				if (comp(*first2, *first1))
//				{
//					if (ret == first1)
//						ret = first2;
//					node1 = first1.getNode();
//					node2 = first2.getNode();
//
//					node2->prev->next		= node2->next;
//					node2->next->prev		= node2->prev;
//
//					node1->prev->next		= node2;
//					node2->prev				= node1->prev;
//
//					node2->next				= node1;
//					node1->prev				= node2;
//					if (first2 == last1)
//					{
//						++first2;
//						last1 = first2;
//					}
//					else
//						++first2;
//				}
//				else if (first1 != last1)
//					++first1;
//				else
//					++first2;
//			}
//			return ret;
//		}
//
//		template <class Compare>
//		iterator	merge_sort(iterator first, iterator last, Compare comp)
//		{
////			iterator half;
////
////			half = split_lists(first, last);
////
////			if (half == last)
////				return first;
////			first		= merge_sort(first, half, comp);
////			half		= merge_sort(half, last, comp);
////
////			first = merge_sorted_lists(first, half, half, last, comp);
////			return first;
//
//		}

		void		sort() {
			merge_sort(*this);
		}

		iterator		split_lists(list &current)
		{
			if (current.size_ == 1)
				return (current.end());

			iterator fast(current.begin());
			iterator slow(fast);
			iterator end(current.end());

			while (fast != end && ++fast != end)
			{
					++fast;
					++slow;
			}
			if (current.size_ % 2 != 0)
				++slow;
			return (slow);
		}

		void	merge_sort(list &current)
		{
			iterator save_slow	= split_lists(current);
			iterator save_end	= current.end();

			list	new_list(save_slow, save_end);
			erase(save_slow, save_end);
			if (new_list.size_ == 0)
				return ;

			current.sort();
			new_list.sort();

			current.merge(new_list);
		}

		//======================================================================

		void		insert_node(node *const prev_node, node *const next_node, value_type val) {
			node *new_node	= new node(val);
			new_node->next	= next_node;
			new_node->prev	= prev_node;
			prev_node->next	= new_node;
			next_node->prev = new_node;
			this->size_++;
		}

		void		relink(node *const prev_node, node *const next_node, node *new_node) {
			new_node->next	= next_node;
			new_node->prev	= prev_node;
			prev_node->next	= new_node;
			next_node->prev = new_node;
		}

		void		delete_node(node *to_delete)
		{
			to_delete->next->prev = to_delete->prev;
			to_delete->prev->next = to_delete->next;
			delete to_delete;
			size_--;
		}

	}; /** end of class LIST */

//=================== Non-member function overloads ============================
	template <class T, class Alloc>
	void swap(list<T,Alloc> &x, list<T,Alloc> &y) {
		 fl::swap(x, y);
	}

//==============================================================================
	template<class T, typename Node>
	bool operator==(const ft::list<T, Node> &lhs, const ft::list<T, Node> &rhs) {
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equalx(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<class T, typename Node>
	bool operator!=(const ft::list<T, Node> &lhs, const ft::list<T, Node> &rhs) {
		return (!(lhs == rhs));
	}

	template<class T, typename Node>
	bool operator<(const ft::list<T, Node> &lhs, const ft::list<T, Node> &rhs) {
		return (fl::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<class T, typename Node>
	bool operator>(const ft::list<T, Node> &lhs, const ft::list<T, Node> &rhs) {
		return (fl::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	}

	template<class T, typename Node>
	bool operator>=(const ft::list<T, Node> &lhs, const ft::list<T, Node> &rhs) {
		return (!(lhs < rhs));
	}

	template<class T, typename Node>
	bool operator<=(const ft::list<T, Node> &lhs, const ft::list<T, Node> &rhs) {
		return (!(lhs > rhs));
	}
} /** end of namespace */