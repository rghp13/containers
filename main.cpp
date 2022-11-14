/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:39:18 by rponsonn          #+#    #+#             */
/*   Updated: 2022/11/14 15:25:06 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <deque>
#if 0
	namespace ft = std;
	#include <map>
	#include <stack>
	#include <vector>
#else
	#include "includes/map.hpp"
	#include "includes/stack.hpp"
	#include "includes/vector.hpp"
#endif
 #include <stdlib.h>

 #define MAX_RAM 4294967296
 #define BUFFER_SIZE 4096
/* struct Buffer
 {
 	int idx;
 	char buff[BUFFER_SIZE];
 };
int main(void)
{
	ft::vector<int> qwe;
	ft::vector<int>::iterator ptr;
	ft::vector<int>::const_iterator cptr;
	ft::vector<int>::reverse_iterator rptr;
	for (int i = 0; i < 50; i++)
		qwe.push_back(i);
	rptr = qwe.rbegin();
	std::cout << *rptr << std::endl;
	ptr = qwe.begin();
	cptr = ptr;
	if (cptr == ptr)
		std::cout << "HI WORLD\n";
	cptr = qwe.begin();
	cptr += 3;
	while (*ptr < 5)
	{
		std::cout << *ptr << std::endl;
		ptr++;
	}
	std::cout << qwe[600] << std::endl;
}

 #define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

int main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}
	std::cout << map_int.size() << std::endl;
	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
		map_int.erase(access);
	}
	std::cout << map_int.size() << std::endl;
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
	return (0);
}*/
int main()
{
	ft::stack<float>								other_stack;
	ft::vector<std::string>							lst;

	lst.push_back("salut");
	lst.push_back("tu vas bien?");
	lst.push_back("super");
	lst.push_back("et toi?");

	ft::stack<std::string, ft::vector<std::string> >	my_stack(lst);

	std::cout << std::boolalpha << other_stack.empty() << std::endl;
	other_stack.push(8.5); // 8.5;
	other_stack.push(42.4242); // 8.5; 42.4242;
	std::cout << other_stack.size() << '\n'; // 2
	other_stack.pop(); // 8.5;
	std::cout << other_stack.size() << '\n'; // 1
	other_stack.push(78541.987); // 8.5; 78541.987;
	std::cout << other_stack.size() << '\n'; // 2
	std::cout << other_stack.top() << '\n'; //78541.987
	std::cout << std::boolalpha << other_stack.empty() << std::endl;

	const std::string const_top = my_stack.top();

	std::cout << "const top: " << const_top << '\n';

	while (!my_stack.empty())
	{
		std::cout << my_stack.top() << '\n';
		my_stack.pop();
	}

	return (0);
}