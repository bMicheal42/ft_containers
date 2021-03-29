#include "containers/vector.class.hpp"
//#include "containers/queue.class.hpp"
#include "containers/list.class.hpp"
#include "containers/multiset.class.hpp"
#include "containers/set.class.hpp"
#include "containers/map.class.hpp"

#include <iostream>
#include <set>
#include <vector>
#include <list>
#include <map>

#define lib ft

#include <iostream>
#include <set>

int main ()
{
	ft::set<int> myset;

	for (int i=1; i<=5; i++) myset.insert(i*10);   // myset: 10 20 30 40 50

	std::pair<ft::set<int>::const_iterator,ft::set<int>::const_iterator> ret;
	ret = myset.equal_range(30);

	std::cout << "the lower bound points to: " << *ret.first << '\n';
	std::cout << "the upper bound points to: " << *ret.second << '\n';

	return 0;
}
