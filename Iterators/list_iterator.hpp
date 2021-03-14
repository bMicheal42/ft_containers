#pragma once

#include "../containers/list.class.hpp"


template <class T>
struct Node;

namespace ft {

// =========================================================================
// --------------------------- LIST_ITERATOR -----------------------------
// =========================================================================
	template<typename T, typename Pointer = T*, typename Reference = T&>
	class list_iterator
	{

	public:
		typedef std::bidirectional_iterator_tag			iterator_category;
		typedef T 										value_type;
		typedef Pointer									pointer;
		typedef Reference								reference;
		typedef ptrdiff_t								difference_type;
		typedef size_t									size_type;
		typedef list_iterator<T, Pointer, Reference>	iter_type;
		typedef list_iterator<T, T *, T &>				iterator;
		typedef list_iterator<T, const T *, const T &>	const_iterator;
		typedef Node<T>									node_ptr;

	private:
		node_ptr										*node_;
//
	public:

		node_ptr *getNode() const { return (node_); }

//		// =================== CONSTRUCTORS / DESTRUCTOR =======================
		list_iterator(iterator other_node = 0) : node_(other_node) {}
//		list_iterator() {}

		list_iterator(node_ptr *lst) { node_(lst); }
//
		list_iterator(list_iterator<T, T*, T&> &copy)
			:node_(const_cast<pointer>(copy.getNode()))
		{} // ?? xz
//
		~list_iterator() {}

//		// Operators ===========================================================

	// '='
		list_iterator &operator=(list_iterator<T, T *, T &> const &a)
		{
			if (this != &a)
				node_ = a.node_;
			return (*this);
		}
	// '*'
		reference operator*() const { return (node_->data); }
	// '->'
		pointer operator->() const { return &(node_->data); }

	// '++ pre'
		iter_type &operator++() {
			node_ = node_->next;
			return (*this);
		}
	// '++ post'
		iter_type operator++(int)
		{
			iter_type tmp = *this;
			node_ = node_->next;
			return (tmp);
		}
	// '-- pre'
		iter_type &operator--()
		{
			node_ = node_->prev;
			return (*this);
		}
//
//		// '-- post'
		iter_type operator--(int)
		{
			iter_type tmp = *this;
			node_ = node_->prev;
			return (tmp);
		}
	}; //end of class

	template<typename TL, typename ptrL, typename refL, typename TR, typename ptrR, typename refR>
	bool operator==(const list_iterator<TL, ptrL, refL> &lhs, const list_iterator<TR, ptrR, refR> &rhs)
	{
		return (lhs.getNode() == rhs.getNode());
	}
	template<typename TL, typename ptrL, typename refL, typename TR, typename ptrR, typename refR>
	bool operator!=(const list_iterator<TL, ptrL, refL> &lhs, const list_iterator<TR, ptrR, refR> &rhs)
	{
		return !(lhs.getNode() == rhs.getNode());
	}
}// end of namespace