#pragma once

#define set__iterator__                 ft::multiset_iterator<Key, Key*, Key&>
#define const__set__iterator__          ft::multiset_iterator<Key, const Key*, const Key&>
#define set_reverse__iterator__         fl::reverse_iterator<iterator>
#define const__set_reverse__iterator__  fl::reverse_iterator<const_iterator>
#define set__                           ft::multiset <value_type, Compare, Alloc>

#include "../utils.hpp"
#include "vector.class.hpp"
#include "multiset.class.hpp"
#include "../Iterators/multiset_iterator.hpp"

// =============================================================================
/** ------------------------------ SET CLASS ---------------------------------*/
// =============================================================================

namespace ft {

	template<class Key, class Compare = std::less<Key>, class Alloc = std::allocator<Key> >
	class set
	{

	public:

		typedef Key                                                 keytype;
		typedef Key                                                 value_type;
		typedef Compare                                             key_compare;
		typedef Compare                                             value_compare;
		typedef Alloc                                               allocator_type;
		typedef size_t                                              size_type;
		typedef ptrdiff_t                                           difference_type;
		typedef Key*                                                pointer;
		typedef const Key*                                          const_pointer;
		typedef Key&                                                reference;
		typedef const Key&                                          const_reference;
		typedef set__iterator__                                     iterator;
		typedef const__set__iterator__                              const_iterator;
		typedef set_reverse__iterator__                             reverse_iterator;
		typedef const__set_reverse__iterator__                      const_reverse_iterator;

	private:

		set__                                                         set_;
		allocator_type                                                alloc_;
		value_compare                                                 compare_;

//======================= CONSTRUCTORS / DESTRUCTORS ===========================

	public:

		explicit set(const Compare& comp = key_compare(), const Alloc& alloc = Alloc())
			:set_(), alloc_(alloc), compare_(comp)
		{}

		template <class InputIterator>
		set (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
			:alloc_(alloc), compare_(comp)
		{
			insert(first, last);
		}

		set (const set &x)
				:set_(x.set_), alloc_(x.alloc_), compare_(x.compare_)
		{}

		set& operator= (const set &x)
		{
			if (this != &x)
			{
				set_        =    x.set_;
				alloc_      =    x.alloc_;
				compare_    =    x.compare_;
			}
			return (*this);
		}

		~set()
		{
			set_.~multiset();
		}

// ================================== ITERATORS ================================

		iterator                    begin()                 { return iterator(this->set_.begin()); }

		const_iterator              begin() const           { return const_iterator(this->set_.begin()); }

		reverse_iterator            rbegin()                { return reverse_iterator(this->set_.rbegin()); }

		const_reverse_iterator      rbegin() const          { return reverse_iterator(this->set_.rbegin()); }

		iterator                    end()                   { return iterator(this->set_.end()); }

		const_iterator              end() const             { return const_iterator(this->set_.end()); }

		reverse_iterator            rend()                  { return reverse_iterator(this->set_.rend()); }

		const_reverse_iterator      rend() const            { return reverse_iterator(this->set_.rend()); }

// ================================== CAPACITY =================================

		bool        empty() const
		{
			return set_.empty();
		}

		size_type   size() const
		{
			return set_.size();
		}

		size_type   max_size() const
		{
			return set_.max_size();
		}
		
// ================================== Modifiers ================================

		// --------------------------- INSERT ----------------------------------

		std::pair<iterator, bool>   insert (const value_type & val)
		{
			iterator pos(set_.find(val));
			if (pos != this->end())
				return std::pair<iterator, bool>(pos, false); // нашли элемент

			iterator it(set_.insert(val));
			return std::pair<iterator, bool>(it, true);
		}

		iterator                    insert (iterator position, const value_type& val)
		{
			(void) position; // thanks for a hint

			iterator pos(set_.find(val));
			if (pos != this->end())
				return pos; // нашли элемент

			iterator it(set_.insert(val));
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

		// --------------------------- ERASE -----------------------------------

		void        erase (iterator position)
		{
			set_.erase(position);
		}

		size_type   erase (const value_type& val)
		{
			return set_.erase(val);
		}

		void        erase (iterator first, iterator last)
		{
			while (first != last)
			{
				erase(first);
				--last;
			}
		}
		// --------------------------- SWAP ------------------------------------

		void        swap (set &x)
		{
			set_.swap(x.set_);
			fl::swap(compare_, x.compare_);
			fl::swap(alloc_, x.alloc_);
		}
		// ---------------------------- CLEAR ----------------------------------

		void        clear()
		{
			set_.clear();
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

		iterator    find (const value_type& val)
		{
			if (this->size() == 0)
				return this->end();
			return set_.find(val);
		}

		size_type   count (const value_type& val)
		{
			if (this->size() == 0)
				return 0;

			iterator it(find(val));
			if (it == set_.end())
				return 0;
			return 1;
		}

		iterator    lower_bound (const value_type& val)
		{
			return set_.lower_bound(val);
		}

		iterator    upper_bound (const value_type& val)
		{
			return set_.upper_bound(val);
		}

		std::pair<iterator,iterator> equal_range (const value_type& val)
		{
			iterator first     = lower_bound(val);
			iterator second    = upper_bound(val);
			return std::pair<iterator, iterator>(first, second);
		}
	}; //end of class set
} //enf of namespace