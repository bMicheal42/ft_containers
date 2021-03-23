#pragma once

#define	fl std
#include <list>
#include "../utils.hpp"
#include "../Iterators/list_iterator.hpp"

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

			const_iterator x_end(x.end()); //for complexity

			for(const_iterator it = x.begin(); it != x_end; ++it)
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
			while(first != last)
				splice(position, x, first++);
		}

		// ----------------------- REMOVE --------------------------------------
        void        remove (const value_type &val) {
            value_type tmp_val = val;
            iterator tmp(begin());
            while(tmp != this->end())
            {
                if (tmp.getNode()->data == tmp_val)
                    tmp = erase(tmp);
                ++tmp;
            }
        }

        template <class Predicate>
        void        remove_if (Predicate pred) {
            iterator tmp(begin());
            while (tmp != this->end())
            {
                if (pred(tmp.getNode()->data) == true)
                    tmp = erase(tmp);
                ++tmp;
            }
        }
		// ----------------------- UNIQUE --------------------------------------
		void		unique() {
			if (this->size_ < 2)
				return;
			iterator tmp(begin());
			++tmp;
			while (tmp !=this->end())
			{
				if (*tmp == tmp.getNode()->prev->data)
					delete_node(tmp.getNode()->prev);
				++tmp;
			}
		}

		template <class BinaryPredicate>
		void		unique (BinaryPredicate binary_pred) {
			if (this->size_ < 2)
				return;
			iterator tmp(begin());
			++tmp;
			while (tmp !=this->end())
			{
				if (binary_pred(*tmp, tmp.getNode()->prev->data))
					delete_node(tmp.getNode()->prev);
				++tmp;
			}
		}

		// ----------------------- MERGE --------------------------------------
		void		merge (list &x) {
			if (&x == this)
				return ;

			iterator it1	= this->begin();
			iterator end	= this->end();
			iterator it_x1	= x.begin();
			iterator x_end	= x.end();

			while (it1 != end && it_x1 != x_end)
			{
				if ((*it_x1) < (*it1))
				{
					++it_x1;
					relink(it1.getNode()->prev, it1.getNode(), it_x1.getNode()->prev);
				}
				else
					++it1;
			}
			if (it_x1 != x_end)
			{
				it_x1.getNode()->prev			= it1.getNode()->prev;
				it1.getNode()->prev->next		= it_x1.getNode();
				x_end.getNode()->prev->next		= last_;
				last_->prev						= x_end.getNode()->prev;
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
		template <class Compare>
		void sort (Compare comp) {
			if (size_)
				merge_sort(*this, comp);
		}

		void		sort() {
			if (size_)
				merge_sort(*this,  ft::my_comp<value_type>);
		}

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
	private:

		iterator		split_lists(list &current)
		{
			if (current.size_ == 1)
				return (current.end());

			Node* fast = current.begin().getNode();
			Node* slow = fast;
			while (fast != current.last_ && fast->next != current.last_)
			{
				fast = fast->next->next;
				slow = slow->next;
			}
			if (current.size_ % 2 != 0)
				slow = slow->next;
			return (iterator(slow));
		}

		template<class Compare>
		void	merge_sort(list &current, Compare comp)
		{
			iterator save_slow	= split_lists(current);
			iterator save_end	= current.end();

			list	new_list(save_slow, save_end);
			while(save_slow != save_end)
			{
				node *tmp_node(save_slow.getNode());
				++save_slow;
				delete_node(tmp_node);
			}

			if (current.size_ == 1)
			{
				if (new_list.size_ > 0)
					current.merge(new_list);
				return;
			}

			if (current.size_ == 2)
			{
				node *node1 = current.begin().getNode();
				node *node2 = node1->next;
				if (comp(node1->data, node2->data))
				{
					node2->next->prev = node2->prev;
					node2->prev->next = node2->next;
					node1->prev->next = node2;
					node2->prev = node1->prev;
					node1->prev = node2;
					node2->next = node1;
				}
				new_list.sort();
				current.merge(new_list);
				return;
			}
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
