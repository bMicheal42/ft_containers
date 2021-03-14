#include "containers/vector.class.hpp"
#include "containers/queue.class.hpp"
#include "containers/list.class.hpp"

#include <iostream>
#include <vector>
#include <list>

int	main() {

	ft::list<int> my_lst;

	my_lst.push_back(5);
	my_lst.push_back(6);
	my_lst.push_back(7);
	my_lst.push_back(8);
	my_lst.push_back(9);

	my_lst.begin();

//	for (; it != my_lst.end(); it++)
//		std::cout << *it << ' ';
//	std::cout << std::endl;
	return 0;
}