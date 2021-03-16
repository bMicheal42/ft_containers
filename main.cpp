#include "containers/vector.class.hpp"
//#include "containers/queue.class.hpp"
#include "containers/list.class.hpp"

#include <iostream>
#include <vector>
#include <list>

#define lib ft

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
	lib::list<int> lst(3,3);
	lst.push_back(4);
	lst.push_back(5);
	lst.assign(0,666);
//	lst.resize(5); std::cout << "size: "<< lst.size() << std::endl;
//	lst.resize(10, 5); 		std::cout << "size: "<< lst.size() << std::endl;
//	lst.resize(5, 5); 		std::cout << "size: "<< lst.size() << std::endl;
//	lst.resize(0, 5); 		std::cout << "size: "<< lst.size() << std::endl;
//	lst.clear();					std::cout << "size: "<< lst.size() << std::endl;
	return 0;
}
