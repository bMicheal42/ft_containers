#pragma once
#include <iostream>
#include "../utils.hpp"
#include "vector.class.hpp"
#include "../Iterators/multiset_iterator.hpp"

// =============================================================================
/** ------------------------------ MULTISET CLASS ----------------------------*/
// =============================================================================
namespace ft {

	template<class Key, class Compare = std::less<Key>, class Alloc = std::allocator<Key> >
	class multiset
	{
	public:

		typedef Key                                      		    keytype;
		typedef Key                                     		    value_type;
		typedef Compare												key_compare;
		typedef Compare												value_compare;
		typedef Alloc											allocator_type;
		typedef size_t												size_type;
		typedef ptrdiff_t											difference_type;
		typedef Key*                 								pointer;
		typedef const Key*                							const_pointer;
		typedef Key&                 								reference;
		typedef const Key&                                          const_reference;
		typedef ft::multiset_iterator<Key, Key*, Key&>              iterator;
		typedef ft::multiset_iterator<Key, const Key*, const Key&>  const_iterator;
		typedef fl::reverse_iterator<iterator>                      reverse_iterator;
		typedef fl::reverse_iterator<const_iterator>                const_reverse_iterator;

	private:

		ft::vector<Key, Alloc>										mset_;
		allocator_type												alloc_;
		key_compare													compare_;

//======================= CONSTRUCTORS / DESTRUCTORS ===========================
	public:

		explicit multiset(const Compare& comp = key_compare(), const Alloc& alloc = Alloc())
			:mset_(), alloc_(alloc), compare_(comp)
        {}

		template <class InputIterator>
		multiset (InputIterator first, InputIterator last,
				  const key_compare& comp = key_compare(),
				  const allocator_type& alloc = allocator_type())
				:alloc_(alloc), compare_(comp)
		{
			insert(first, last);
		}

		multiset (const multiset &x)
				:mset_(x.mset_), alloc_(x.alloc_), compare_(x.compare_)
		{}

		multiset& operator= (const multiset &x)
		{
			if (this != &x)
			{
				mset_		=	x.mset_;
				alloc_ 		= 	x.alloc_;
				compare_ 	= 	x.compare_;
			}
			return (*this);
		}

		~multiset()
		{
			mset_.~vector();
		}

// ================================== ITERATORS ================================

		iterator					begin()					{ return iterator(this->mset_.begin().base()); }

		const_iterator				begin() const			{ return const_iterator(this->mset_.begin().base()); }

		reverse_iterator			rbegin()				{ return reverse_iterator(this->mset_.end().base()); }

		const_reverse_iterator		rbegin() const			{ return reverse_iterator(this->mset_.end().base()); }

		iterator					end() 					{ return iterator(this->mset_.end().base()); }

		const_iterator				end() const				{ return const_iterator(this->mset_.end().base()); }

		reverse_iterator			rend()					{ return reverse_iterator(this->mset_.begin().base()); }

		const_reverse_iterator		rend() const			{ return reverse_iterator(this->mset_.begin().base()); }

// ================================== CAPACITY =================================

		bool empty() const
		{
			return mset_.empty();
		}

		size_type size() const
		{
			return mset_.size();
		}

		size_type max_size() const
		{
			return mset_.max_size();
		}
// ================================== Modifiers ================================

		// --------------------------- INSERT ----------------------------------

		iterator insert (const value_type & val)
		{
			if (mset_.size() == 0)
				return iterator (mset_.insert(mset_.begin(), val));
			value_type  tmp = val;
			iterator it(find_pos(tmp));
			if (compare_(*it, val))
				++it;
			return iterator(mset_.insert(it.getIt(), val));
		}

		iterator insert (iterator position, const value_type& val)
		{
			(void)position; // thanks for a hint!
			return insert(val);
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				insert(*first);
				++first;
			}
		}
		// --------------------------- ERASE -----------------------------------

		void erase (iterator position)
		{
			mset_.erase(position.getIt());
		}

		size_type erase (const value_type& val)
		{
			value_type tmp = val;
			iterator   it(find_pos(val));
			size_type  i = 0;
			for (; !compare_(*it, tmp) && !compare_(tmp, *it); ++i)
			{
				erase(it);
				it = find_pos(tmp);
			}
			return i;
		}

		void erase (iterator first, iterator last)
		{
			for (;first != last; --last)
				erase(first);
		}
		// --------------------------- SWAP ------------------------------------

		void swap (multiset &x)
		{
			mset_.swap(x.mset_);
			fl::swap(compare_, x.compare_);
			fl::swap(alloc_, x.alloc_);
		}
		// ---------------------------- CLEAR ----------------------------------

		void clear()
		{
			mset_.clear();
		}

//================================ OBSERVES ====================================

		key_compare key_comp() const
		{
			return compare_;
		}

		value_compare value_comp() const
		{
			return compare_;
		}
//================================ OPERATIONS ==================================

		iterator find (const value_type& val)
		{
			iterator it (find_pos(val));
			if (compare_(val, *it) || compare_(*it, val))
				return this->end();
			return iterator (find_pos(val));
		}

		size_type count (const value_type& val)
		{
			iterator it (find_pos(val));
			if (compare_(val, *it) || compare_(*it, val))
				return 0;
			size_type	n = 1;


			iterator last = it;
			for (; *it == val && it != this->begin(); --it)
				;

			if (*it != val)
				++it;

			for (; it != last; ++it, ++n)
				;
			return n;
		}

		iterator lower_bound (const value_type& val)
		{
			iterator it (find_pos(val));
			if (compare_(val, *it) || compare_(*it, val))
				return this->end();

			iterator last = it;
			for (; *it == val && it != this->begin(); --it)
				;

			if (*it != val)
				++it;

			return it;
		}

		iterator upper_bound (const value_type& val)
		{
			iterator it (find_pos(val));
			if (compare_(val, *it) || compare_(*it, val))
				return this->end();

			iterator last = it;
			for (; *it == val && it != this->begin(); --it)
				;

			if (*it != val)
				++it;

			for (; it != last; ++it)
				;
			return ++it;
		}

		std::pair<iterator,iterator> equal_range (const value_type& val)
		{
			iterator first	= lower_bound(val);
			iterator second	= upper_bound(val);
			return std::pair<iterator, iterator>(first, second);
		}
//===================================== MY =====================================

	private:

		iterator find_pos(const value_type &val)
		{
			if (mset_.size() == 0)
				return begin();
			return iterator(mset_.begin() + binary_search(val, 0, mset_.size()));
		}

		size_type 		binary_search(const value_type &val, size_type start, size_type size)
		{
			if (size == 1)
				return start;

			size_type half = start + size / 2 + (size % 2);
			if (compare_(val, mset_[half]))
				return (binary_search(val, start, half - start));
			else
				return (binary_search(val, half, start + size - half));
		}

	};//enf of multiset class
}// end of namespace

