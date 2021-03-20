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

#include <ctime>

void ft_sort_comp_test() {

	ft::list<int> mouse;
	for (int i = 1000; i > 0; --i)
		mouse.push_back(i);

	size_t full_time = 0;

	unsigned  int time;

	for (int i = 0; i < 3000; ++i)
	{
		time = clock();

		mouse.sort();

		full_time += (clock() - time);
		mouse.reverse();
	}

	mouse.sort();
	std::cout << "Average time is: " << full_time / 3000 << std::endl;


//(void)time;
//	mouse.push_back(3);
//	mouse.push_back(5);
//	mouse.push_back(13);
//	mouse.push_back(9);
//	mouse.push_back(6);

//	for (ft::list<int>::iterator it = mouse.begin(); it != mouse.end(); ++it) {
//		std::cout << *it << " ";
//	}
//	std::cout << std::endl;
//
//	ft::list<int> empty;
//
//	empty.sort(comp);
//	for (ft::list<int>::iterator it = empty.begin(); it != empty.end(); ++it) {
//		std::cout << *it << " ";
//	}
//	std::cout << std::endl;
//
//	ft::list<int> reverse;
//	reverse.push_back(10);
//	reverse.push_back(9);
//	reverse.push_back(8);
//	reverse.push_back(7);
//	reverse.push_back(6);
//	reverse.push_back(5);
//
//	reverse.sort(comp);
//	for (ft::list<int>::iterator it = reverse.begin(); it != reverse.end(); ++it) {
//		std::cout << *it << " ";
//	}
//	std::cout << std::endl;
}

int main()
{
	ft_sort_comp_test();
}
