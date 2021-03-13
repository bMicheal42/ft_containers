#pragma once

# include <deque>

namespace ft {

// =============================================================================
// ------------------------------ QUEUE CLASS ----------------------------------
// =============================================================================

	template <class T, class Container = std::deque<T> >
	class queue
	{

	public:
		typedef T			value_type;
		typedef Container	container_type;
		typedef size_t		size_type;

		explicit			queue(const container_type &ctnr = container_type()) : c_(ctnr) {}
		bool				empty() const { return (this->c_.empty()); }
		value_type			&front() { return (this->c_.front()); }
		const value_type	&front() const { return (this->c_.front()); }
		value_type			&back() { return (this->c_.back()); }
		const value_type	&back() const { return (this->c_.back()); }
		void				pop() { this->c_.pop_front(); }
		void				push(const value_type &val) { this->c_.push_back(val); }
		size_type			size() const { return (this->c_.size()); }

		template <class TT, class CContainer>
		friend bool operator==(const queue<TT, CContainer> &lhs, const queue<TT,CContainer> &rhs);

		template <class TT, class CContainer>
		friend bool operator<(const queue<TT, CContainer> &lhs, const queue<TT,CContainer> &rhs);

	private:
		container_type c_;

	};//end of QUEUE class

// =========================== NO MEMBER FUNCTIONS =============================

	template <class T, class Container>
		bool operator==(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
		{ return (lhs.c_ == rhs.c_); }

	template <class T, class Container>
	bool operator<(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
	{ return (lhs.c_ < rhs.c_); }

	template <class T, class Container>
		bool operator!=(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
		{ return !(lhs == rhs); }

	template <class T, class Container>
		bool operator<=(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
		{ return !(rhs < lhs); }

	template <class T, class Container>
		bool operator>(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
		{ return (rhs < lhs); }

	template <class T, class Container>
		bool operator>=(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
		{ return !(lhs < rhs); }

} // end of NAMESPACE