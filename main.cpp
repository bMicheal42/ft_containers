//#include "containers/vector.class.hpp"
//#include "containers/queue.class.hpp"
#include "containers/list.class.hpp"

#include <iostream>
#include <vector>
#include <list>

#define lib ft

int	main() {

	lib::list<int> a(1,3);

	a.push_back(4);
	a.push_back(5);
	a.push_back(6);
	a.push_back(7);
	a.push_back(8);

//	lib::list<int>::iterator it1(++a.begin());
//	lib::list<int>::iterator it2(it1);
//
//	it2++;
//	it2++;

	lib::list<int> my = a;
//	a.pop_front();
//	a.pop_back();
	std::cout << "lol";


//	ft::list<int>::const_iterator arr = a.begin();
//	ft::list<int>::const_iterator arr2(++a.begin());

//	if (arr2 == arr)
//		std::cout << "non equal" << std::endl;

//	my_lst.push_back(5);
//	my_lst.push_back(6);
//	my_lst.push_back(7);
//	my_lst.push_back(8);
//	my_lst.push_back(9);

//	my_lst.begin();

//	for (; it != my_lst.end(); it++)
//		std::cout << *it << ' ';
//	std::cout << std::endl;
	return 0;
}