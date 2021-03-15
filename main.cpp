//#include "containers/vector.class.hpp"
//#include "containers/queue.class.hpp"
#include "containers/list.class.hpp"

#include <iostream>
#include <vector>
#include <list>


int	main() {

	ft::list<int> a;
	a.push_front(2);
	a.push_front(3);
//	a.pop_front();
	a.pop_back();
	std::cout << "lol";
//	a.push_back(4);
//	a.push_back(5);

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