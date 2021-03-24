#pragma once

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
				:mset_(first, last), alloc_(alloc), compare_(comp)
		{}

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




//		iterator find_pos(const value_type &val, size_type index, size_type size)
//		{
//
//			if (size == 1)
//				return (iterator(&this->mset_[index]));
//
//			size_type half(index);
//
//			for (size_type i = 0; i < size / 2; ++i, ++half)
//				;
//			if (compare_(val, this->mset_[half]))
//				return (find_pos(val, index, size % 2 + size / 2));
//
//			else if (compare_(this->mset_[half], val))
//				return (find_pos(val, half + (size % 2 != 0), size / 2));
//
//			else
//				return iterator(&this->mset_[half]);
//		}

		size_type find_pos(const value_type &val, size_type start, size_type size)
		{
				if (val > mset_[size])
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
					return find_pos(val, half, size - start);
				else
					return (half);
		}
// --------------------------------- INSERT ------------------------------------

//		iterator insert (const value_type& val)
//		{
//			iterator it(&this->mset_[find_pos(val, 0, mset_.size() - 1)]);
//			mset_.
//
//		}
//
//		iterator insert (iterator position, const value_type& val)
//		{
//			return (inse)
//		}
//
//		template <class InputIterator>
//		void insert (InputIterator first, InputIterator last)
//		{
//
//		}
	};//enf of multiset class
}// end of namespace

