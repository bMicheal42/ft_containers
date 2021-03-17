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

int	main()
{

//	lib::vector<const int> it(8, 5);
//
//	lib::vector<const int>::const_iterator it1 = it.begin();
//	lib::vector<const int>::const_iterator it2(it.end() - 1);
//	if (it1 != it2)
//		std::cout << *it1 << " Gdrive privuet " << *it2 << std::endl;
//	if (it1 == it2)
//		std::cout << *it1 << " Gdrive pokaaa (error) " << *it2 << std::endl;
//	 (*it)++; //error check

/**	 work with STD code / not working with MY */

//	lib::vector<const int> vec(8, 6);
//	lib::vector<int>::const_iterator it1 = vec.begin();
//	lib::vector<int>::const_iterator it2(vec.end() - 1);
//	if (it1 != it2)
//		std::cout << *it1 << " Gdrive privuet " << *it2 << std::endl;
//	if (it1 == it2)
//		std::cout << *it1 << " Gdrive pokaaa (error) " << *it2 << std::endl;

//	(*vec)++; //error check
//	vec.insert(vec.begin(), 2, 1); //check error
//	vec.push_back(1); //check error


//	lib::list<const int> lst;
//	lib::list<const int>::const_iterator it1 = lst.begin();
//	lib::list<const int>::const_iterator it2(lst.begin());
//	it2--;
//	if (it1 != it2)
//		std::cout << *it1 << " Gdrive privuet " << *it2 << std::endl;
//	lst.erase(lst.begin());
	lib::list<int> lst2;
	for (int i = 0; i < 5;++i)
		lst2.push_back(i + 10);
	lib::list<int>::iterator lst2_it(lst2.begin());
	lst2_it++; lst2_it++; lst2_it++; // na 13

	lib::list<int> lst(1,3);
	lst.push_back(4);
	lst.push_back(5);
	lst.push_back(6);
	lst.push_back(7);
	lst.push_back(8);

	printf_list(lst, "List before: ");
	printf_list(lst2, "List2 before: ");

	lib::list<int>::iterator position(lst.begin());
	position++; position++; position++;				 // pos = 6;

	lib::list<int>::iterator it1(lst.begin()); 		//it = 3

	lib::list<int>::iterator it2(lst.begin());
	it2++; it2++; it2++; 								// it2 = 6



	std::cout << "it1: " << *it1 << " it2: " << *it2 << std::endl;

	lst.insert(position, it1, it2);

	printf_list(lst, "List after insert : ");
	std::cout << "it1: " << *it1 << " it2: " << *it2 << std::endl;

//	lst.assign(it1, it2);
//
//	printf_list(lst, "List after assign: ");
//	std::cout << "it1: " << *it1 << " it2: " << *it2 << std::endl;

//	lst.erase(it1, it2);
//	printf_list(lst, "List after erase: ");
//	printf_list(lst2, "List2 after erase: ");


	lst.splice(it2, lst2, lst2_it);
	printf_list(lst, "List after splice: ");
	printf_list(lst2, "List2 after splice: ");

//	lst.splice(position, lst2, lst2_it, lst2.end());
//	printf_list(lst, "List after splice: ");
//	printf_list(lst2, "List2 after splice: ");

//	lst.assign(0,666);
//	lst.resize(5); std::cout << "size: "<< lst.size() << std::endl;
//	lst.resize(10, 5); 		std::cout << "size: "<< lst.size() << std::endl;
//	lst.resize(5, 5); 		std::cout << "size: "<< lst.size() << std::endl;
//	lst.resize(0, 5); 		std::cout << "size: "<< lst.size() << std::endl;
//	lst.clear();					std::cout << "size: "<< lst.size() << std::endl;
	return 0;
}
