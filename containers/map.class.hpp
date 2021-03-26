#pragma once

#define map__iterator__ ft::multiset_iterator<value_type, value_type*, value_type&>
#define const__map__iterator__ ft::multiset_iterator<value_type, const value_type*, const value_type&>
#define map__reverse__iterator__ fl::reverse_iterator<iterator>
#define const__map__reverse__iterator__ fl::reverse_iterator<const_iterator>
#define avl_tree__ ft::multiset <value_type, ft::less_key<Key, T>, Alloc>
#include "../utils.hpp"
#include "vector.class.hpp"
#include "multiset.class.hpp"
#include "../Iterators/multiset_iterator.hpp"

// =============================================================================
/** ---------------------------------- MAP CLASS -----------------------------*/
// =============================================================================

namespace ft {

	template < class Key, class T, class Compare = ft::less_key<Key, T>,
	        class Alloc = std::allocator<std::pair<const Key, T> > >

	class map
	{

	public:

		typedef Key					                          	    key_type;
		typedef std::pair<const Key, T>                    		    value_type;
		typedef T													mapped_type;
		typedef Compare												key_compare;
		typedef Alloc												allocator_type;
		typedef size_t												size_type;
		typedef ptrdiff_t											difference_type;
		typedef Key*                 								pointer;
		typedef const Key*                 							const_pointer;
		typedef Key&                 								reference;
		typedef const Key&                                          const_reference;
		typedef map__iterator__							            iterator;
		typedef const__map__iterator__								const_iterator;
		typedef map__reverse__iterator__		                    reverse_iterator;
		typedef const__map__reverse__iterator__		                const_reverse_iterator;

	private:

		avl_tree__													map_;
		allocator_type												alloc_;
		key_compare													compare_;

//======================= CONSTRUCTORS / DESTRUCTORS ===========================
	public:
		explicit map (const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type())
			:map_(), alloc_(alloc), compare_(comp)
		{}

//		template <class InputIterator>
//		map (InputIterator first, InputIterator last,
//			 const key_compare& comp = key_compare(),
//			 const allocator_type& alloc = allocator_type())
//		{
//
//		}

		map (const map& x)
			:map_(x.map_), alloc_(x.alloc_), compare_(x.compare_)
		{}

		~map()
		{
			map_.~multiset();
		}

		map& operator= (const map& x)
		{
			if (this != &x)
			{
				map_		=	x.map_;
				alloc_ 		= 	x.alloc_;
				compare_ 	= 	x.compare_;
			}
			return (*this);
		}

// ================================== ITERATORS ================================

		iterator					begin()					{ return map_.begin(); }

		const_iterator				begin() const			{ return map_.begin(); }

		reverse_iterator			rbegin()				{ return map_.rbegin(); }

		const_reverse_iterator		rbegin() const			{ return map_.rbegin(); }

		iterator					end() 					{ return map_.end(); }

		const_iterator				end() const				{ return map_.end(); }

		reverse_iterator			rend()					{ return map_.rend(); }

		const_reverse_iterator		rend() const			{ return map_.rend(); }
// ================================== CAPACITY =================================

		bool empty() const
		{
			return map_.empty();
		}

		size_type size() const
		{
			return map_.size();
		}

		size_type max_size() const
		{
			return map_.max_size();
		}
// ================================== Modifiers ================================

		mapped_type& operator[] (const key_type &k)
		{
			iterator pos(map_.find(value_type(k, 0)));
			return	(*pos).second;
		}

	};// end of class map
}//end of namespace
