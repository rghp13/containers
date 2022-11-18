/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:39:18 by rponsonn          #+#    #+#             */
/*   Updated: 2022/11/18 14:30:38 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <deque>
#if 0 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include <includes/map.hpp>
	#include <includes/stack.hpp>
	#include <includes/vector.hpp>
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096

bool	vectortest(void)
{
	std::cout << "Vector test" << std::endl;
	ft::vector<int> myvector;
	ft::vector<int>::iterator it;

	// set some initial values:
	std::cout << "Set some values" << std::endl;
	for (int i = 1; i <= 5; i++)
		myvector.push_back(i); // 1 2 3 4 5
	for (ft::vector<int>::iterator tmp = myvector.begin(); tmp < myvector.end(); tmp++)
		std::cout << ' ' << *tmp;
	std::cout << std::endl;
	it = myvector.begin();
	++it; // it points now to number 2           ^
	std::cout << "Insert 10 before 2" << std::endl;
	myvector.insert(it, 10); // 1 10 2 3 4 5
	for (ft::vector<int>::iterator tmp = myvector.begin(); tmp < myvector.end(); tmp++)
		std::cout << ' ' << *tmp;
	std::cout << std::endl;
	// "it" still points to number 2                      ^
	std::cout << "Insert 20 twice before 10" << std::endl;
	myvector.insert(it, 2, 20); // 1 20 20 10 2 3 4 5
	for (ft::vector<int>::const_iterator tmp = myvector.begin(); tmp < myvector.end(); tmp++)
		std::cout << ' ' << *tmp;
	std::cout << std::endl;
	++it; // it points now to the second 20            ^

	ft::vector<int> anothervector(2, 30);
	std::cout << "Insert 30 twice before the second 20 from another vector" << std::endl;
	myvector.insert(it, anothervector.begin(), anothervector.end());
	// 1 20 30 30 20 10 2 3 4 5
	for (ft::vector<int>::iterator tmp = myvector.begin(); tmp < myvector.end(); tmp++)
		std::cout << ' ' << *tmp;
	std::cout << std::endl;
	// "it" no longer valid, get a new one:
	it = myvector.begin();

	ft::vector<int> yetanothervector(2, 40);
	std::cout << "Insert 40 twice before 30 from another vector" << std::endl;
	myvector.insert(it + 2, yetanothervector.begin(), yetanothervector.end());
	// 1 20 40 40 30 30 20 10 2 3 4 5

	std::cout << "myvector contains:";
	for (it = myvector.begin(); it < myvector.end(); it++)
		std::cout << ' ' << *it;
	std::cout << std::endl;
	yetanothervector = myvector;
	return (true);
}
bool map_test(void)
{
	std::cout << "Map test" << std::endl;
	ft::map<char, int> mymap;

	// first insert function version (single parameter):
	mymap.insert(ft::pair<char, int>('a', 100));
	mymap.insert(ft::pair<char, int>('z', 200));

	ft::pair<ft::map<char, int>::iterator, bool> ret;
	ret = mymap.insert(ft::pair<char, int>('z', 500));
	if (ret.second == false)
	{
		std::cout << "element 'z' already existed";
		std::cout << " with a value of " << ret.first->second << '\n';
	}

	// second insert function version (with hint position):
	ft::map<char, int>::iterator it = mymap.begin();
	mymap.insert(it, ft::pair<char, int>('b', 300)); // max efficiency inserting
	mymap.insert(it, ft::pair<char, int>('c', 400)); // no max efficiency inserting

	// third insert function version (range insertion):
	ft::map<char, int> anothermap;
	anothermap.insert(mymap.begin(), mymap.find('c'));

	// showing contents:
	std::cout << "mymap contains:\n";
	for (it = mymap.begin(); it != mymap.end(); it++)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "anothermap contains:\n";
	for (it = anothermap.begin(); it != anothermap.end(); it++)
		std::cout << it->first << " => " << it->second << '\n';
	ft::map<int,int> mymap2;
	std::cout << "inserting 10million elements" << std::endl;
	for (int i=0; i<10000000; i++)
		mymap2.insert(ft::pair<int,int>(i, i));
	std::cout << "mymap2 contains: " << mymap2.size() << " elements" << std::endl;
	for (ft::map<int,int>::iterator it = mymap2.begin(); it != mymap2.end(); it++)
		;//std::cout << it->first << std::endl;
	return (true);
}
bool stack_test(void)
{
	std::cout << "Stack test" << std::endl;
	ft::stack<int> mystack;

	for (int i = 0; i < 20; ++i)
		mystack.push(i);

	std::cout << "Popping out elements...";
	while (!mystack.empty())
	{
		std::cout << ' ' << mystack.top();
		mystack.pop();
	}
	std::cout << std::endl;
	return (true);
}
int main(void)
{
	vectortest();
	map_test();
	stack_test();
	return (0);
}