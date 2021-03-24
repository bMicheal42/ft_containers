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
	for (int i = 100000; i > 0; --i)
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
	for (int i = 0; i < 1000000; i++) {
		vec.push_back(i);
	}

	ft::multiset<int> mset1(vec.begin(), vec.end());

	unsigned  int time;
	size_t full_time = 0;

//	print_array(mset1);
//	mset1.insert(30);
//	print_array(mset1);


//	print_array(mset1);

	for (int i = 0; i < 10; ++i)
	{
		time = clock();

		mset1.insert(666666);
//
//		std::cout << mset1.find_pos(45, 0, mset1.size() - 1) << std::endl;

//		std::cout << *it << std::endl;
		full_time += clock() - time;
	}
//	print_array(mset1);
	std::cout << "Average time is: " << full_time / 10 << std::endl;
}

//int main()
//{
////	ft_sort_comp_test();
////	binary_iters_test();
////	binary_index_test();
//
//
//	ft::vector<int> vec;
//	for (int i = 1; i < 6; i++) {
//		vec.push_back(i * 11);
//	}
//	ft::multiset<int> mset1(vec.begin(), --vec.end());
//
//	ft::vector<int> vec2;
//	for (int i = 1; i < 6; i++) {
//		vec2.push_back(i * 10);
//	}
//	ft::multiset<int> mset2(vec2.begin(), vec2.end());
//	ft::multiset<int>::iterator it(mset2.begin());
//	ft::multiset<int>::iterator it2(--mset2.end());
//
//	std::cout << "Before: "; print_array(mset1);
//
////	int arr[] = {10, 40, 20, 30, 50, 0};
////	ft::multiset<int>::iterator it(arr);
////	ft::multiset<int>::iterator it2(arr + 5);
//
//
//	mset1.insert(it, it2);
//
//	std::cout << "After: "; print_array(mset1);
//}

int main ()
{
	ft::multiset<int> mymultiset;
	ft::multiset<int>::iterator it;

	// insert some values:
	mymultiset.insert (40);                            // 40
	mymultiset.insert (40);                            // 40
	mymultiset.insert (40);                            // 40
	for (int i=1; i<7; i++) mymultiset.insert(i*10);   // 10 20 30 40 40 50 60
//	print_array(mymultiset);
	it=mymultiset.begin();
	it++;                                              //    ^

	mymultiset.erase(it);                             // 10 30 40 40 50 60
//	print_array(mymultiset);
	mymultiset.erase (40);                             // 10 30 50 60

	for (it=mymultiset.begin(); it!=mymultiset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
//	print_array(mymultiset);

	mymultiset.insert (40);
	mymultiset.insert (70);
	mymultiset.insert (70);
	mymultiset.insert (5);
	mymultiset.insert (5);
	mymultiset.insert (5);
	mymultiset.erase ( it, --mymultiset.end() );         // 10 30

//	print_array(mymultiset);
	for (it=mymultiset.begin(); it!=mymultiset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	return 0;
}
