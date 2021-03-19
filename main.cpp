#include "containers/vector.class.hpp"
//#include "containers/queue.class.hpp"
#include "containers/list.class.hpp"

#include <iostream>
#include <vector>
#include <list>

#define lib ft


void	printf_list(lib::list<int> &list, std::string bef_aft)
{
	std::cout << "\n======================================================" << std::endl;
	std::cout << bef_aft; // List before/ after
	for (lib::list<int>::iterator iter(list.begin()); iter != list.end(); iter++)
		std::cout << *iter << " ";
	std::cout << std::endl;
	std::cout << bef_aft << "size: " << list.size() << std::endl;
	std::cout << "======================================================\n" << std::endl;
}

//int	main()
//{
//
////	lib::vector<const int> it(8, 5);
////
////	lib::vector<const int>::const_iterator it1 = it.begin();
////	lib::vector<const int>::const_iterator it2(it.end() - 1);
////	if (it1 != it2)
////		std::cout << *it1 << " Gdrive privuet " << *it2 << std::endl;
////	if (it1 == it2)
////		std::cout << *it1 << " Gdrive pokaaa (error) " << *it2 << std::endl;
////	 (*it)++; //error check
//
///**	 work with STD code / not working with MY */
//
////	lib::vector<const int> vec(8, 6);
////	lib::vector<int>::const_iterator it1 = vec.begin();
////	lib::vector<int>::const_iterator it2(vec.end() - 1);
////	if (it1 != it2)
////		std::cout << *it1 << " Gdrive privuet " << *it2 << std::endl;
////	if (it1 == it2)
////		std::cout << *it1 << " Gdrive pokaaa (error) " << *it2 << std::endl;
//
////	(*vec)++; //error check
////	vec.insert(vec.begin(), 2, 1); //check error
////	vec.push_back(1); //check error
//
//
////	lib::list<const int> lst;
////	lib::list<const int>::const_iterator it1 = lst.begin();
////	lib::list<const int>::const_iterator it2(lst.begin());
////	it2--;
////	if (it1 != it2)
////		std::cout << *it1 << " Gdrive privuet " << *it2 << std::endl;
////	lst.erase(lst.begin());
//	lib::list<int> lst2;
//	for (int i = 0; i < 5;++i)
//		lst2.push_back(i + 10);
//	lib::list<int>::iterator lst2_it(lst2.begin());
//	lst2_it++; lst2_it++; lst2_it++; // na 13
//
//	lib::list<int> lst(1,3);
//	lst.push_back(4);
//	lst.push_back(5);
//	lst.push_back(6);
//	lst.push_back(7);
//	lst.push_back(8);
//
//	printf_list(lst, "List before: ");
//	printf_list(lst2, "List2 before: ");
//
//	lib::list<int>::iterator position(lst.begin());
//	position++; position++; position++;				 // pos = 6;
//
//	lib::list<int>::iterator it1(lst.begin()); 		//it = 3
//
//	lib::list<int>::iterator it2(lst.begin());
//	it2++; it2++; it2++; 								// it2 = 6
//
//
//
//	std::cout << "it1: " << *it1 << " it2: " << *it2 << std::endl;
//
//	lst.insert(position, it1, it2);
//
//	printf_list(lst, "List after insert : ");
//	std::cout << "it1: " << *it1 << " it2: " << *it2 << std::endl;
//
////	lst.assign(it1, it2);
////
////	printf_list(lst, "List after assign: ");
////	std::cout << "it1: " << *it1 << " it2: " << *it2 << std::endl;
//
////	lst.erase(it1, it2);
////	printf_list(lst, "List after erase: ");
////	printf_list(lst2, "List2 after erase: ");
//
//
//	lst.splice(it2, lst2, lst2_it);
//	printf_list(lst, "List after splice: ");
//	printf_list(lst2, "List2 after splice: ");
//
////	lst.splice(position, lst2, lst2_it, lst2.end());
////	printf_list(lst, "List after splice: ");
////	printf_list(lst2, "List2 after splice: ");
//
////	lst.assign(0,666);
////	lst.resize(5); std::cout << "size: "<< lst.size() << std::endl;
////	lst.resize(10, 5); 		std::cout << "size: "<< lst.size() << std::endl;
////	lst.resize(5, 5); 		std::cout << "size: "<< lst.size() << std::endl;
////	lst.resize(0, 5); 		std::cout << "size: "<< lst.size() << std::endl;
////	lst.clear();					std::cout << "size: "<< lst.size() << std::endl;
//	return 0;
//}

//#include <cmath>
//bool same_integral_part (double first, double second)
//{ return ( int(first)==int(second) ); }
//
//// a binary predicate implemented as a class:
//struct is_near {
//	bool operator() (double first, double second)
//	{ return (fabs(first-second)<5.0); }
//};

//int main ()
//{
//	double mydoubles[]={ 12.15,  2.72, 73.0,  12.77,  3.14,
//						 12.77, 73.35, 72.25, 15.3,  72.25 };
//	std::list<double> mylist (mydoubles,mydoubles+10);
//
//	mylist.sort();      //  2.72,  3.14, 12.15, 12.77, 12.77,
//	// 15.3,  72.25, 72.25, 73.0,  73.35
//
//	mylist.unique();           //  2.72,  3.14, 12.15, 12.77
//	// 15.3,  72.25, 73.0,  73.35
//
//	mylist.unique (same_integral_part);  //  2.72,  3.14, 12.15
//	// 15.3,  72.25, 73.0
//
//	mylist.unique (is_near());           //  2.72, 12.15, 72.25
//
//	std::cout << "mylist contains:";
//	for (std::list<double>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
//		std::cout << ' ' << *it;
//	std::cout << '\n';
//
//	return 0;
//}

int main() {
	lib::list<int> list1;
	list1.push_back(421);
	list1.push_back(2);
	list1.push_back(33);
//	list1.push_back(5);
//	list1.push_back(16);
//	list1.push_back(124);
//	list1.push_back(125);

	lib::list<int> list2;
//	list2.push_back(9);
//	list2.push_back(8);
	list2.push_back(7);
	list2.push_back(6);
	list2.push_back(5);
	list2.push_back(4);
	list2.push_back(3);
	list2.push_back(2);

// list1.merge(list1);
// swap(list1, list2);
// list2.sort();
	ft::list<int>::iterator it1 = list2.begin();
	ft::list<int>::iterator it2 = list2.end();

	list2.sort();
// printf_list(list1, "List 1: ");
	printf_list(list2, "List 2: ");
// if (list1 > list2)
// std::cout << "Well!" << std::endl;
 }