#pragma once

#include <deque>

namespace ft {

// =============================================================================
/** ----------------------------- STACK CLASS --------------------------------*/
// =============================================================================

	template<class T, class Container = std::deque <T> >
	class stack
	{

	public:
		typedef T            value_type;
		typedef Container    container_type;
		typedef size_t       size_type;

		explicit             stack(const container_type &ctnr = container_type()) :c_(ctnr) {}
		bool                 empty() const { return (this->c_.empty()); }
		size_type            size() const { return (this->c_.size()); }
		value_type           &top() { return (this->c_.back()); }
		const value_type     &top() const { return (this->c_.back()); }
		void                 push (const value_type& val) { return (this->c_.push_back(val)); }
		void                 pop() { return (this->c_.pop_back()); }

		template <class TT, class CContainer>
		friend bool operator==(const stack<TT, CContainer> &lhs, const stack<TT,CContainer> &rhs);

		template <class TT, class CContainer>
		friend bool operator<(const stack<TT, CContainer> &lhs, const stack<TT,CContainer> &rhs);

	private:
		container_type      c_;

	}; //end of class Stack

	// ========================= NO MEMBER FUNCTIONS ===========================

	template <class T, class Container>
	bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs.c_ == rhs.c_);
	}

	template <class T, class Container>
	bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs.c_ < rhs.c_);
	}

	template <class T, class Container>
	bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Container>
	bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Container>
	bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Container>
	bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return !(lhs < rhs);
	}

} // end of namespace