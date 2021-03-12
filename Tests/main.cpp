#include "../vector.class.hpp"
#include <vector>
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
	std::vector<int> arr(10);
	std::vector<int> arr2(10);

	for (int i = 0; i < 10; ++i)
		arr[i] = i + 10; // 10,11,12,13,14,15,16,17,18,19

	for (int i = 0; i < 10; ++i)
		arr2[i] = i + 70; // 70,71,72,73,74,75,76,77,78,79
//	std::cout << arr[9].some << std::endl;

//	arr.insert(arr.begin(), 2, 3); // arr: 3,3,10,11,12,13,14,15,16,17,18,19
//	for (int i = 0; i < 10; ++i) {
//		arr[i].alloc(); }
//	arr2.insert(arr2.end(), arr.begin(), arr.begin());
	arr2.assign(arr2.begin(), arr2.end() - 2);
	for (size_t i = 0; i < arr2.size(); ++i)
		std::cout << arr2[i] << " ";
	std::cout << std::endl;
	return 0;
}
