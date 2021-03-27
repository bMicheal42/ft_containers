#pragma once

#define map__iterator__                 ft::multiset_iterator<value_type, value_type*, value_type&>
#define const__map__iterator__          ft::multiset_iterator<value_type, const value_type*, const value_type&>
#define map__reverse__iterator__        fl::reverse_iterator<iterator>
#define const__map__reverse__iterator__ fl::reverse_iterator<const_iterator>
#define avl_tree__                      ft::multiset <value_type, Compare, Alloc>

#include "../utils.hpp"
#include "vector.class.hpp"
#include "multiset.class.hpp"
#include "../Iterators/multiset_iterator.hpp"
 
// =============================================================================
/** ---------------------------------- MAP CLASS -----------------------------*/
// =============================================================================

namespace ft {

	template < class Key, class T, class Compare = ft::less_key<Key, T>,
			class Alloc = std::allocator<std::pair<Key, T> > >

	class map
	{

	public:

		typedef Key                                                    key_type;
		typedef T                                                      mapped_type;
		typedef std::pair<Key, T>                                      value_type;
		typedef Compare                                                key_compare;
		typedef Compare                                                value_compare;
		typedef Alloc                                                  allocator_type;
		typedef size_t                                                 size_type;
		typedef ptrdiff_t                                              difference_type;
		typedef Key*                                                   pointer;
		typedef const Key*                                             const_pointer;
		typedef Key&                                                   reference;
		typedef const Key&                                             const_reference;
		typedef map__iterator__                                        iterator;
		typedef const__map__iterator__                                 const_iterator;
		typedef map__reverse__iterator__                               reverse_iterator;
		typedef const__map__reverse__iterator__                        const_reverse_iterator;

	private:
		avl_tree__                                                      map_;
		allocator_type                                                  alloc_;
		key_compare                                                     compare_;
//======================= CONSTRUCTORS / DESTRUCTORS ===========================
	public:
		explicit map (const key_compare &comp = key_compare(),
				const allocator_type& alloc = allocator_type())
			:map_(), alloc_(alloc), compare_(comp)
		{}

        template <class InputIterator>
        map (InputIterator first, InputIterator last,
             const key_compare& comp = key_compare(),
             const allocator_type& alloc = allocator_type())
             :alloc_(alloc), compare_(comp)
        {
			insert(first, last);
        }

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
				map_        =     x.map_;
				alloc_      =     x.alloc_;
				compare_    =     x.compare_;
			}
			return (*this);
		}

// ================================== ITERATORS ================================

		iterator                    begin()                  { return map_.begin(); }

		const_iterator              begin() const            { return map_.begin(); }

		reverse_iterator            rbegin()                 { return map_.rbegin(); }

		const_reverse_iterator      rbegin() const           { return map_.rbegin(); }

		iterator                    end()                    { return map_.end(); }

		const_iterator              end() const              { return map_.end(); }

		reverse_iterator            rend()                   { return map_.rend(); }

		const_reverse_iterator      rend() const             { return map_.rend(); }
// ================================== CAPACITY =================================

		bool                        empty() const
		{
			return map_.empty();
		}

		size_type                   size() const
		{
			return map_.size();
		}

		size_type                   max_size() const
		{
			return map_.max_size();
		}
// ================================== Modifiers ================================

		mapped_type&    operator[] (const key_type &k)
		{
			return (*((this->insert(fl::make_pair(k,mapped_type()))).first)).second;
		}

		std::pair<iterator, bool>   insert (const value_type& val)
		{
			iterator pos(map_.find(val));
			if (pos != this->end())
				return std::pair<iterator, bool>(pos, false); // нашли элемент

			iterator it(map_.insert(val));
			return std::pair<iterator, bool>(it, true);
		}

		iterator                    insert (iterator position, const value_type& val)
		{
			(void) position; // thanks for a hint

			iterator pos(map_.find(val));
			if (pos != this->end())
				return pos; // нашли элемент

			iterator it(map_.insert(val));
			return it;
		}

		template <class InputIterator>
		void                        insert (InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				insert(*first);
				++first;
			}
		}

		void                        erase (iterator position)
		{
			map_.erase(position);
		}

		size_type                   erase (const key_type& k)
		{
			return map_.erase(std::pair<key_type, mapped_type>(k, T()));
		}

		void                        erase (iterator first, iterator last)
		{
			while (first != last)
			{
				erase(first);
				--last;
			}
		}

		void                        swap (map& x)
		{
			map_.swap(x.map_);
			fl::swap(compare_, x.compare_);
			fl::swap(alloc_, x.alloc_);
		}

		void                        clear()
		{
			map_.clear();
		}
//================================ OBSERVES ====================================

		key_compare                              key_comp() const
		{
			return compare_;
		}

		value_compare                            value_comp() const
		{
			return compare_;
		}
//================================ OPERATIONS ==================================

		iterator                                 find (const key_type &k)
		{
			if (this->size() == 0)
				return this->end();
			return map_.find(std::pair<key_type, mapped_type>(k, T()));
		}

		const_iterator                            find (const key_type &k) const
		{
			if (this->size() == 0)
				return this->end();
			return map_.find(std::pair<key_type, mapped_type>(k, T()));
		}

		size_type                                 count (const key_type& k)
		{
			if (this->size() == 0)
				return 0;

			iterator it(find(k));
			if (it == map_.end())
				return 0;
			return 1;
		}

		iterator                                 lower_bound (const key_type& k)
		{
			return map_.lower_bound(std::pair<key_type, mapped_type>(k, T()));
		}

		const_iterator                            lower_bound (const key_type& k) const
		{
			return map_.lower_bound(std::pair<key_type, mapped_type>(k, T()));
		}

		iterator                                  upper_bound (const key_type& k)
		{
			return map_.upper_bound(std::pair<key_type, mapped_type>(k, T()));
		}

		const_iterator                             upper_bound (const key_type& k) const
		{
			return map_.upper_bound(std::pair<key_type, mapped_type>(k, T()));
		}

		std::pair<const_iterator,const_iterator>   equal_range (const key_type& k) const
		{
			const_iterator first     = lower_bound(k);
			const_iterator second    = upper_bound(k);
			return std::pair<iterator, iterator>(first, second);
		}

		std::pair<iterator,iterator>               equal_range (const key_type& k)
		{
			iterator first     = lower_bound(k);
			iterator second    = upper_bound(k);
			return std::pair<iterator, iterator>(first, second);
		}
	};// end of class map
}//end of namespace
