#pragma once

#include "../containers/list.class.hpp"
#include "../utils.hpp"

namespace ft {

// =============================================================================
/** ------------------------------ LIST_ITERATOR ------------------------------*/
// =============================================================================

	template<typename T, typename Node, typename Pointer = T*, typename Reference = T&>
	class list_iterator
	{

	public:
		typedef std::bidirectional_iterator_tag						iterator_category;
		typedef T 													value_type;
		typedef Pointer												pointer;
		typedef Reference											reference;
		typedef ptrdiff_t											difference_type;
		typedef size_t												size_type;
		typedef Node												*node_ptr;

	private:
		node_ptr													node_;

	public:

		node_ptr getNode() const { return (this->node_); }

//========================= CONSTRUCTORS / DESTRUCTOR ==========================

		list_iterator(node_ptr node = 0) :node_(node) {}

		list_iterator(list_iterator<T, Node, T*, T&> const &copy) :node_(copy.getNode()) {}

		~list_iterator() {}

//================================ OPERATORS ===================================

	// '='
		list_iterator	&operator=(list_iterator &other)
		{
			if (&other != this)
				node_ = other.node_;
			return (*this);
		}

	// '*'
		reference		operator*() const { return (node_->data); }

	// '->'
		pointer			operator->() const { return &(node_->data); }


	// '++ pre'
		list_iterator	&operator++() {
			node_ = node_->next;
			return (*this);
		}

	// '++ post'
		list_iterator	operator++(int) {
			list_iterator tmp = *this;
			node_ = node_->next;
			return (tmp);
		}

	// '-- pre'
		list_iterator	&operator--()	{
			node_ = node_->prev;
			return (*this);
		}

	// '-- post'
		list_iterator	operator--(int) {
			list_iterator tmp = *this;
			node_ = node_->prev;
			return (tmp);
		}

		bool operator==(list_iterator<T, Node, T*, T&> &it) const  { return (it.node_ == node_); }
		bool operator!=(list_iterator<T, Node, T*, T&> &it) const  { return (it.node_ != node_); }

	}; /** end of class */

} /** end of namespace */