#pragma once
#include <iostream>
#include "../utils.hpp"
#include "vector.class.hpp"
#include "../Iterators/multiset_iterator.hpp"

// =============================================================================
/** ------------------------------ MULTISET CLASS ----------------------------*/
// =============================================================================
namespace ft {

	template<class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
	class multiset
	{
	public:

		typedef Key                                      		    keytype;
		typedef Key                                     		    value_type;
		typedef Compare												key_compare;
		typedef Compare												value_compare;
		typedef Allocator											allocator_type;
		typedef size_t												size_type;
		typedef ptrdiff_t											difference_type;
		typedef Key*                 								pointer;
		typedef const Key*                 							const_pointer;
		typedef Key&                 								reference;
		typedef const Key&                                          const_reference;
		typedef ft::multiset_iterator<Key, Key*, Key&>              iterator;
		typedef ft::multiset_iterator<Key, const Key*, const Key&>  const_iterator;
		typedef fl::reverse_iterator<iterator>                      reverse_iterator;
		typedef fl::reverse_iterator<const_iterator>                const_reverse_iterator;

	private:

		ft::vector<Key, Allocator>									mset_;
		allocator_type												alloc_;
		key_compare													compare_;

//======================= CONSTRUCTORS / DESTRUCTORS ===========================
	public:

		explicit multiset(const Compare& comp = key_compare(), const Allocator& alloc = Allocator())
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
// =============================================================================

// --------------------------------- CAPACITY ----------------------------------

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

		size_type find_pos(const value_type &val, size_type start, size_type size)
		{
				if (mset_.size()  == 0)
					return 0;

				if (val > mset_[mset_.size() - 1])
					return size + 1;

				if (val < mset_[start])
					return start + (val > mset_[start]);

				size_type half = start + size / 2;

				if (size == 1)
				{
					return start + (val > mset_[start]);
				}

				if (val < mset_[half])
					return find_pos(val, start, half - start);
				else if (mset_[half] < val)
					return find_pos(val, half, size);
				else
					return (half);
		}


		// --------------------------- INSERT ----------------------------------

		iterator insert (const value_type & val)
		{
			iterator it(&mset_[find_pos(val, 0, mset_.size() - 1)]);
			mset_.insert(it.getIt(), val);
			return it;
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
			size_type n = 0;
			iterator it(&mset_[find_pos(val, 0, mset_.size() - 1)]);
			for(; *it == tmp; ++n)
				erase(it);
			return n;
		}

		void erase (iterator first, iterator last)
		{
			for (;first != last; --last)
				erase(first);
		}

	};//enf of multiset class
}// end of namespace

