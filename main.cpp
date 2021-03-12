#include "vector.class.hpp"
#include "queue.class.hpp"
#include "list.class.hpp"
#include <iostream>

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
	ft::vector<Test> arr(10, 7);
	std::cout << arr[9].some << std::endl;

	arr.insert(arr.end(),2, 3);
	for (int i = 0; i < 10; ++i) {
		arr[i].alloc();
	}
	return 0;
}