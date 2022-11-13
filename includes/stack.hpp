/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:07:06 by rponsonn          #+#    #+#             */
/*   Updated: 2022/11/13 21:40:40 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP
//#include <vector>
#include "vector.hpp"
namespace ft
{
	template <typename T, typename Container = ft::vector<T> >
	class stack
	{
		public:
		//types
		typedef T value_type;
		typedef Container container_type;
		typedef typename Container::size_type	size_type;
	//constructors
	explicit	stack(const container_type &ctnr = container_type()): c(ctnr) {}
				stack(const stack	&other): c(other.c) {}
				//~stack(void) {}for some reasons stacks don't need destructors?
				//member functions size,empty,top,push,pop
		protected:
		container_type c;
		public:
	value_type	&top(void)
	{	return (c.back());}
	value_type	&top(void)const
	{	return (c.back());}
	bool		empty(void)const
	{	return (c.empty());}
	size_type	size(void)const
	{	return (c.size());}
	void		push(const value_type &value)
	{	return (c.push_back(value));}
	void		pop(void)
	{	c.pop_back();}
		//need at least 1 friend
		//template <typename T, class container_type>
		friend bool operator<(const stack<T, container_type> &lhs, const stack<T, container_type> &rhs)
		{
			return (lhs.c < rhs.c);
		}
		//template <typename T, class container_type>
		friend bool operator==(const stack<T, container_type> &lhs, const stack<T, container_type> &rhs)
		{
			return (lhs.c == rhs.c);
		}
	};
	//operator != == <= > >=
	//needs template
	template <typename T, class container_type>
	bool operator!=(const stack<T, container_type> &lhs, const stack<T, container_type> &rhs)
	{
		return (!(lhs == rhs));
	}
	template <typename T, class container_type>
	bool operator<=(const stack<T, container_type> &lhs, const stack<T, container_type> &rhs)
	{
		return (!(rhs < lhs));
	}
	template <typename T, class container_type>
	bool operator>(const stack<T, container_type> &lhs, const stack<T, container_type> &rhs)
	{
		return (rhs < lhs);
	}
	template <typename T, class container_type>
	bool operator>=(const stack<T, container_type> &lhs, const stack<T, container_type> &rhs)
	{
		return (!(lhs < rhs));
	}
} // namespace ft

#endif