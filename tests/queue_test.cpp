#include "../containers/queue.class.hpp"
#include <queue>
#include <iostream>

void	telly() {
	{
		ft::queue<int> MyQueue;
		std::cout << MyQueue.empty() << std::endl;
		std::cout << MyQueue.size() << std::endl;
	}
	std::cout << std::endl;
	{
		ft::queue<int> MyQueue;
		std::cout << MyQueue.empty() << std::endl;
		MyQueue.push(88);
		std::cout << MyQueue.back() << std::endl;
		MyQueue.push(44);
		std::cout << MyQueue.back() << std::endl;
		std::cout << MyQueue.size() << std::endl;
		MyQueue.pop();
		std::cout << MyQueue.size() << std::endl;
		std::cout << MyQueue.back() << std::endl;
		MyQueue.pop();
		std::cout << MyQueue.size() << std::endl;
	}
	std::cout << std::endl;
	{
		ft::queue<int> MyQueue;
		std::cout << MyQueue.empty() << std::endl;
		MyQueue.push(88);
		std::cout << MyQueue.front() << std::endl;
		MyQueue.push(44);
		std::cout << MyQueue.front() << std::endl;
		std::cout << MyQueue.size() << std::endl;
		MyQueue.pop();
		std::cout << MyQueue.size() << std::endl;
		std::cout << MyQueue.front() << std::endl;
		MyQueue.pop();
		std::cout << MyQueue.size() << std::endl;
	}
	{
		ft::queue<int> MyQueue1;
		ft::queue<int> MyQueue2;

		MyQueue1.push(100);
		MyQueue1.push(44);

		MyQueue2.push(100);
		MyQueue2.push(44);

		if (MyQueue1 == MyQueue2)
			std::cout << "MyQueue1 is equal to MyQueue2" << std::endl;
		if (MyQueue1 < MyQueue2)
			std::cout << "MyQueue1 is smaller than MyQueue2" << std::endl;
		if (MyQueue1 <= MyQueue2)
			std::cout << "MyQueue1 is smaller than or equal to MyQueue2" << std::endl;
		if (MyQueue1 > MyQueue2)
			std::cout << "MyQueue1 is larger than MyQueue2" << std::endl;
		if (MyQueue1 >= MyQueue2)
			std::cout << "MyQueue1 is larger than or equal to MyQueue2" << std::endl;
	}
}


int	main() {
	telly();
	return 0;
}
