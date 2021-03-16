#include "../containers/vector.class.hpp"
#include <vector>
#include <string>
#include <iostream>


template< typename T >
void	print_container_content(std::vector<T> &vec, std::string name = "container") {
	std::cout << name << " contains:";
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << ' ' << *it;
	std::cout << " $" << std::endl;
}

template< typename T >
void	reverse_print_container_content(std::vector<T> &vec, const std::string& name = "container") {
	std::cout << name << " contains:";
	for (std::vector<int>::reverse_iterator it = vec.rbegin(); it != vec.rend(); it++)
		std::cout << ' ' << *it;
	std::cout << " $" << std::endl;
}

void	constructors_test() {
	int i = 8;
	std::vector<int> def;
	print_container_content(def, "default constructor");
	std::vector<int>	fill(i, 42);
	for (int i = 0; i < 8; i++)
		fill.push_back( i );
	print_container_content(fill, "fill constructor");
	std::vector<int> range(fill.begin(), fill.end());
	print_container_content(range, "range constructor");
	std::vector<int> copy(range);
	print_container_content(copy, "copy constructor");
	copy = def;
	print_container_content(copy, "assignation operator");
}

void	iterators_test() {
	std::vector<int> hats;
	for (int i = 0; i < 72; i++)
		hats.push_back(i * 10);
	std::vector<int>::iterator		it = hats.begin();
	std::vector<int>::iterator		ite = hats.end();
	ite--;
	std::vector<int>::iterator test = 5 + it;
	std::cout << "*test = " << *test << std::endl;
	std::cout << "*it = " << *it << ", *ite = " << *ite << std::endl;
	std::vector<int>::const_iterator	cit = hats.begin();
	std::vector<int>::const_iterator	cite = hats.end();
	cite--;
	std::cout << "sfhkdsfh" << std::endl;
	std::cout << "*cit = " << *cit << ", *cite = " << *cite << std::endl;
	std::vector<int>::reverse_iterator		rit = hats.rbegin();
	std::vector<int>::reverse_iterator		rite = hats.rend();
	(void)rite;
	std::vector<int>::const_reverse_iterator	crit = hats.rbegin();
	std::vector<int>::const_reverse_iterator	crite = hats.rend();
	std::cout << "regular iterators:" << std::endl;
	std::cout << "reg: operator==(): " << std::boolalpha << (it == cit) << ", " << (cit == it) << std::endl;
	std::cout << "reg: operator!=(): " << std::boolalpha << (it != cite) << ", " << (cite != it) << std::endl;
	std::cout << "reg: operator<(): " << std::boolalpha << (it < cite) << ", " << (cite < it) << std::endl;
	std::cout << "reg: operator<=(): " << std::boolalpha << (it <= cite) << ", " << (cite <= it) << std::endl;
	std::cout << "reg: operator>(): " << std::boolalpha << (it > cite) << ", " << (cite > it) << std::endl;
	std::cout << "reg: operator>=(): " << std::boolalpha << (it >= cite) << ", " << (cite >= it) << std::endl;
	ite = it;
	std::cout << "*it++ gives: " << *it++ << ", it now is " << *it << std::endl;
	std::cout << "*++it gives: " << *++it << ", it now is " << *it << std::endl;
	std::cout << "*rit++ gives: " << *rit++ << ", it now is " << *rit << std::endl;
	std::cout << "*++rit gives: " << *++rit << ", it now is " << *rit << std::endl;
	std::cout << "*it-- gives: " << *it-- << ", it now is " << *it << std::endl;
	std::cout << "*--it gives: " << *--it << ", it now is " << *it << std::endl;
	std::cout << "*rit-- gives: " << *rit-- << ", it now is " << *rit << std::endl;
	std::cout << "*--rit gives: " << *--rit << ", it now is " << *rit << std::endl;
	// *cit += 10;
	// *crit += 10;
	std::cout << "reverse iterators:" << std::endl;
	std::cout << "reverse: operator==(): " << std::boolalpha << (rit == crit) << ", " << (crit == rit) << std::endl;
	std::cout << "reverse: operator!=(): " << std::boolalpha << (rit != crite) << ", " << (crite != rit) << std::endl;
	std::cout << "reverse: operator<(): " << std::boolalpha << (rit < crite) << ", " << (crite < rit) << std::endl;
	std::cout << "reverse: operator<=(): " << std::boolalpha << (rit <= crite) << ", " << (crite <= rit) << std::endl;
	std::cout << "reverse: operator>(): " << std::boolalpha << (rit > crite) << ", " << (crite > rit) << std::endl;
	std::cout << "reverse: operator>=(): " << std::boolalpha << (rit >= crite) << ", " << (crite >= rit) << std::endl;
	std::cout << "dereference operator on iterators: " << it[2] << ", " << cit[3] << ", " << rit[4] << ", " << crit[5] << " WORK!" << std::endl;
}

void	capacity_test() {
	std::vector<int>	papajohns;

	std::cout << "papajohns.empty(): " << std::boolalpha<< papajohns.empty() << std::endl;
	for (int i = 0; i < 10; ++i)
		papajohns.push_back(i);
	std::cout << "papajohns.size(): " << papajohns.size() << std::endl;
	std::cout << "papajohns.max_size(): " << papajohns.max_size() << std::endl;
	std::cout << "papajohns.capacacity(): " << papajohns.capacity() << std::endl;
	std::cout << "papajohns.empty(): " << std::boolalpha << papajohns.empty() << std::endl;

}

void	element_access_test() {
	std::vector<int> kokkita;

	for (int i = 0; i < 10; ++i)
		kokkita.push_back(-3 * i);

	const std::vector<int> constkita(kokkita);
	std::cout << "kokkita[3]: " << kokkita[3] << ", constkita[4]: " << constkita[4] << std::endl;
	try {
		std::cout << "the [] operator does not check if the input value is inbounds of the array" << std::endl;
		std::cout << "the function .at() does check and throws an exception if it is out of bounds, here I'll show you:" << std::endl;
		std::cout << "kokkita.at(13): " << kokkita.at(13) << std::endl;
	}
	catch (std::exception & e) {
		std::cout << "See? it threw an exception" << std::endl;
		// I didnt print e.what(), because diff will see it as different (and wrong) sadface
	}
	std::cout << "kokkita.front() = " << kokkita.front() << ", constkita.front() = " << constkita.front() << std::endl;
	std::cout << "kokkita.back() = " << kokkita.back() << ", constkita.back() = " << constkita.back() << std::endl;
	// std::cout << "kokkita[" << 812039 << "]: " << kokkita[812039] << std::endl;
}

void	modifiers_test() {

	std::vector<int>	tocopy;
	for (int i = 0; i < 14; ++i)
		tocopy.push_back(14 * i);
	std::vector<int> wap;
	wap.assign(5, 69);
	print_container_content(wap, "after the first assign, wapwap");
	wap.assign(tocopy.begin(), tocopy.end());
	print_container_content(wap, "and after the second, wapwap");
	while (!(tocopy.empty()))
		tocopy.pop_back();
	print_container_content(wap, "wap");
	std::vector<int>::iterator it = wap.begin() + 2;
	std::cout << "*it = " << *it << std::endl;
	wap.insert(it, 2, 800);
	it = wap.insert(wap.begin() + 1, 9999);
	std::cout << "returned iterator from insert gives " << *it << std::endl;
	tocopy.insert(tocopy.begin(), wap.begin(), wap.end() - 5);
	print_container_content(wap, "after insert, wap");

	it = tocopy.erase(tocopy.begin());
	std::cout << "erasing returns iterator to " << *it << std::endl;
	print_container_content(tocopy, "after insert and erasing, tocopy");
	it = tocopy.erase(tocopy.begin(), tocopy.begin() + 6);
	std::cout << "erasing returns iterator to " << *it << std::endl;

	print_container_content(tocopy, "after insert and erasing, tocopy");

}

void	relational_operators_test() {
	std::vector<int>	a;
	std::vector<int>	b;
	for (int i = 0; i < 8; i++) {
		a.push_back(i);
		b.push_back(i);
	}
	std::cout << "this one should return 1: " << (a == b) << ", and this one 0: " << (a != b) << std::endl;
	std::cout << (a < b) << (b < a) << (a <= b) << (b <= a) << std::endl;
	a.push_back(0);
	b.push_back(5);
	std::cout << "now vice versa, should return 0: " << (a == b) << ", and this one 1: " << (a != b) << std::endl;
	std::cout << (a < b) << (b < a) << (a <= b) << (b <= a) << std::endl;
}

void	stl_test() {
	// checking if I can also assign items from STL iterators
	std::vector<int>		wap;
	std::vector<int>	stl;
	for (int i = 0; i < 12; i++)
		stl.push_back(i * 4);
	wap.assign(stl.begin(), stl.end());
	print_container_content(wap, "wap");
	reverse_print_container_content(wap, "wap");
}

void	sam() {
	std::vector<int>	sam(8, 123);
	// int ret = sam.end() - sam.begin();
	int ret = sam.end() - sam.begin();
	std::cout << "ret = " << ret << std::endl;
	sam.resize(5);
	std::cout << "vector capacity: " << sam.capacity() << std::endl;
	std::cout << "vector size: " << sam.size() << std::endl;
	std::cout << "vector front: " << sam.front() << std::endl;
	std::cout << "vector back: " << sam.back() << std::endl;
	sam.resize(8, 100);
	std::cout << "vector capacity: " << sam.capacity() << std::endl;
	std::cout << "vector size: " << sam.size() << std::endl;
	std::cout << "vector front: " << sam.front() << std::endl;
	std::cout << "vector back: " << sam.back() << std::endl;
	sam.resize(12389);
	std::cout << "vector capacity: " << sam.capacity() << std::endl;
	std::cout << "vector size: " << sam.size() << std::endl;
	std::cout << "vector front: " << sam.front() << std::endl;
	std::cout << "vector back: " << sam.back() << std::endl;
}


int	main() {
	stl_test();
	constructors_test();
	iterators_test();
	capacity_test();
	element_access_test();
	modifiers_test();
	relational_operators_test();
	sam();
	return 0;
}

