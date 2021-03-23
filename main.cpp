#include "containers/vector.class.hpp"
//#include "containers/queue.class.hpp"
#include "containers/list.class.hpp"
#include "containers/multiset.class.hpp"

#include <iostream>
#include <set>
#include <vector>
#include <list>
#define lib ft



bool comp(int a, int b) {
	return a < b;
}

#include <ctime>

void ft_sort_comp_test() {

	ft::list<int> mouse;
	for (int i = 1000000; i > 0; --i)
		mouse.push_back(i);

	size_t full_time = 0;

	unsigned  int time;

	for (int i = 0; i < 1; ++i)
	{
		time = clock();

		mouse.sort();

		full_time += (clock() - time);
		mouse.reverse();
	}

//	mouse.sort();
	std::cout << "Average time is: " << full_time / 1 << std::endl;
}
#include <vector>
int main()
{
//	ft_sort_comp_test();
	std::vector<int> vec;
	for (int i = 0; i < 1000; i++) {
		vec.push_back(i);
	}



	ft::multiset<int> mset1(vec.begin(), vec.end());
//	ft::multiset<int> mset2(myints + 1, myints + 2);

	for (ft::multiset<int>::iterator it(mset1.begin()); it != mset1.end(); ++it)
		std::cout << *(it) << " ";
	std::cout << std::endl;

	unsigned  int time;
	time = clock();
	mset1.find_pos(43, 0, mset1.size());
	time == (clock() - time);
	std::cout << "Average time is: " << full_time / 1 << std::endl;

//	mset2 = mset1;
//	std::cout << *mset1.begin() << std::endl;
//	std::cout << *(++mset1.rbegin()) << std::endl;
//	std::cout << *(--mset1.end()) << std::endl;
//	std::cout << *(--mset1.rend()) << std::endl;
//
//	ft::multiset<int>::reverse_iterator it = mset1.rbegin();
//	std::cout << *(it) << " LALKA" << std::endl;
}

