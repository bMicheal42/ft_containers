#include "containers/vector.class.hpp"
//#include "containers/queue.class.hpp"
#include "containers/list.class.hpp"
#include "containers/multiset.class.hpp"

#include <iostream>
#include <set>
#include <vector>
#include <list>
#define lib ft

#include <ctime>

void	print_array(ft::multiset<int> set)
{
	for (ft::multiset<int>::iterator it(set.begin()); it != set.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
};

void	ft_sort_comp_test() {

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

//void	binary_iters_test()
//{
//	std::vector<int> vec;
//	for (int i = 0; i < 1000000; i++)
//	vec.push_back(i);
//
//	ft::multiset<int> mset1(vec.begin(), vec.end());
//
//	unsigned  int time;
//	size_t full_time = 0;
//
//	for (int i = 0; i < 100; ++i)
//	{
//		time = clock();
//		mset1.find_pos(900000, 0, mset1.size());
//		full_time += clock() - time;
//	}
//	std::cout << "min val Average time is: " << full_time / 100 << std::endl;
//}

void	binary_index_test()
{
	std::vector<int> vec;
	for (int i = 1; i < 6; i++) {
		vec.push_back(i * 10);
	}

	ft::multiset<int> mset1(vec.begin(), vec.end());

	unsigned  int time;
	size_t full_time = 0;

	print_array(mset1);
//	for (int i = 1; i < 101; ++i)
//	{
		time = clock();

		size_t pos;
		std::cout << mset1.find_pos(30, 0, mset1.size() - 1) << std::endl;
//		ft::multiset<int>::iterator it(&mset1[pos]);

//		std::cout << *it << std::endl;
		full_time += clock() - time;
//	}
	std::cout << "Average time is: " << full_time << std::endl;
}

int main()
{
//	ft_sort_comp_test();
//	binary_iters_test();
	binary_index_test();


//	int arr[] = {10, 40, 20, 30, 50, 0};
//

}

