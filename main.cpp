#include "containers/vector.class.hpp"
#include "containers/queue.class.hpp"
#include "containers/list.class.hpp"
#include <iostream>
#include <vector>

class   Test {
public:
	Test() : some(0), str(0) {std::cout << "Test created" << std::endl;}

	Test(int s) : some(s), str(0) {std::cout << "Test " << this->some << " created" << std::endl;}

	Test(Test const & s) : some(s.some), str(0) {
		std::cout << "Copy Test " << this->some << " created" << std::endl;
	}

	~Test() {
		if (this->str != 0)
			free(this->str);
		std::cout << "Test deleted" << std::endl;
	}

	Test &operator=(Test const & x) {
		this->str = (char*)malloc(10);
		this->some = x.some;
		return (*this);
	}

	void alloc() {
		this->str = (char*)malloc(10);
	}
	int some;
	char* str;

};

int	main() {
	// Less
//	ft::vector<Test> arr(5, 7);
//	std::cout << "Before: " << arr[9].some << std::endl;
//
////	arr.insert(arr.end(),2, 3);
//	for (int i = 0; i < 10; ++i) {
//		arr[i].alloc();
//	}
//	arr.erase(arr.begin(), arr.begin() + 1);
//// 1 2 3 4 . . 7 8 9
////	std::cout << "AFTER: " << arr[9].some << std::endl;
//	arr[4].some = 12;
//	std::cout << arr[4].some << std::endl;

	ft::vector<Test> arr(5, 7);
	arr.insert(arr.begin() + 2, 2, arr[0]);
	for (int i = 0; i < arr.size(); i++)
		std::cout << arr[i].some << " ";
	std::cout << std::endl;
	return 0;
}