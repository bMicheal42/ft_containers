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

//	mouse.sort();
	std::cout << "Average time is: " << full_time / 3000 << std::endl;
}

int main()
{
	ft_sort_comp_test();
}
