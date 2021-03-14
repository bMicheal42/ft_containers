#include "containers/vector.class.hpp"
#include "containers/queue.class.hpp"
#include "containers/list.class.hpp"

#include <iostream>
#include <vector>
#include <list>

int	main() {

	std::list<int> my_lst;

	my_lst.push_back(5);
	my_lst.push_back(6);
	my_lst.push_back(7);
	my_lst.push_back(8);
	my_lst.push_back(9);

	std::list<int>::iterator omg;
	std::list<int>::iterator omg2;
	if (omg == omg2)
		std::cout << "lol" << std::endl;
	else
		std::cout << "nihuia" << std::endl;
	omg++;
	return 0;
}