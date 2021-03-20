#include "containers/vector.class.hpp"
//#include "containers/queue.class.hpp"
#include "containers/list.class.hpp"

#include <iostream>
#include <vector>
#include <list>
#define lib ft



bool comp(int a, int b) {
	return a < b;
}

void ft_sort_comp_test() {
	std::cout << "sort_comp_test" << std::endl;
	lib::list<int> mouse;
	mouse.push_back(7);
	mouse.push_back(3);
	mouse.push_back(5);
	mouse.push_back(13);
	mouse.push_back(9);
//	mouse.push_back(6);

	mouse.sort();
	for (lib::list<int>::iterator it = mouse.begin(); it != mouse.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
//
//	lib::list<int> empty;
//
//	empty.sort(comp);
//	for (lib::list<int>::iterator it = empty.begin(); it != empty.end(); ++it) {
//		std::cout << *it << " ";
//	}
//	std::cout << std::endl;
//
//	lib::list<int> reverse;
//	reverse.push_back(10);
//	reverse.push_back(9);
//	reverse.push_back(8);
//	reverse.push_back(7);
//	reverse.push_back(6);
//	reverse.push_back(5);
//
//	reverse.sort(comp);
//	for (lib::list<int>::iterator it = reverse.begin(); it != reverse.end(); ++it) {
//		std::cout << *it << " ";
//	}
//	std::cout << std::endl;
}

int main()
{
	ft_sort_comp_test();
}