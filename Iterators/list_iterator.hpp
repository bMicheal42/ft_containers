#pragma once

#include "../containers/list.class.hpp"
#include "../utils.hpp"

namespace ft {

// =============================================================================
/** ------------------------------ LIST_ITERATOR ------------------------------*/
// =============================================================================

	template<typename T, typename  Node, bool Bool>
	class list_iterator
	{

	public:
		typedef std::bidirectional_iterator_tag						iterator_category;
		typedef T 													value_type;
		typedef typename chooseConst<Bool, T*, const T*>::type		pointer;
		typedef typename chooseConst<Bool, T&, const T&>::type		reference;
		typedef ptrdiff_t											difference_type;
		typedef size_t												size_type;
		typedef Node												*node_ptr;

	private:
		node_ptr													node_;
//
	public:

		node_ptr getNode() const { return (this->node_); }

//========================= CONSTRUCTORS / DESTRUCTOR ==========================

		list_iterator(node_ptr node = 0) :node_(node) {}

		list_iterator(const list_iterator<T, Node, false> &copy) :node_(copy.getNode()) {}

		~list_iterator() {}

//================================ OPERATORS ===================================

	// '='
		list_iterator &operator=(const list_iterator &other)
		{
			if (&other != this)
				node_ = other.node_;
			return (*this);
		}

	// '*'
		reference operator*() const { return (node_->data); }

	// '->'
		pointer operator->() const { return &(node_->data); }


	// '++ pre'
		list_iterator &operator++() {
			node_ = node_->next;
			return (*this);
		}

	// '++ post'
		list_iterator operator++(int) {
			list_iterator tmp = *this;
			node_ = node_->next;
			return (tmp);
		}

	// '-- pre'
		list_iterator &operator--()	{
			node_ = node_->prev;
			return (*this);
		}

	// '-- post'
		list_iterator operator--(int) {
			list_iterator tmp = *this;
			node_ = node_->prev;
			return (tmp);
		}

		bool operator==(const list_iterator &it) const  { return (it.node_ == node_); }
		bool operator!=(const list_iterator &it) const  { return (it.node_ != node_); }

	}; /** end of class */

} /** end of namespace */