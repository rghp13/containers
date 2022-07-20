/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:07:06 by rponsonn          #+#    #+#             */
/*   Updated: 2022/07/20 14:04:32 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP
#include <vector>
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
		typedef Container::size_type	size_type;//fix this
	//constructors
	explicit	stack(const container_type &ctnr = container_type()): _ctnr(ctnr) {}
				stack(const stack	&other): _ctnr(other._ctnr) {}
				//~stack(void) {}for some reasons stacks don't need destructors?
				//member functions size,empty,top,push,pop
	value_type	&top(void)
	{	return (_ctnr.back());}
	value_type	&top(void)const
	{	return (_ctnr.back());}
	bool		empty(void)const
	{	return (_ctnr.empty());}
	size_type	size(void)const
	{	return (_ctnr.size());}
	void		push(const value_type &value)
	{	return (_ctnr.push_back(value));}
	void		pop(void)
	{	_ctnr.pop_back();}
		private:
		//need at least 1 friend
		friend bool operator<(const stack &lhs, const stack &rhs)
		{
			return (lhs._ctnr < rhs._ctnr);
		}
		container_type _ctnr;
	};
	//operator != == <= > >=
	//needs template
	template <typename T, class container>
	bool operator!=(const stack<T, container> &lhs, const stack<T, container> &rhs)
	{
		return ((lhs < rhs) || (rhs < lhs));//this could be slow if the stack is huge
	}
	template <typename T, class container>
	bool operator==(const stack<T, container> &lhs, const stack<T, container> &rhs)
	{
		return (!((lhs < rhs) || (rhs < lhs)));
	}
	template <typename T, class container>
	bool operator<=(const stack<T, container> &lhs, const stack<T, container> &rhs)
	{
		return (!(rhs < lhs));
	}
	template <typename T, class container>
	bool operator>(const stack<T, container> &lhs, const stack<T, container> &rhs)
	{
		return (rhs < lhs);
	}
	template <typename T, class container>
	bool operator>=(const stack<T, container> &lhs, const stack<T, container> &rhs)
	{
		return (!(lhs < rhs));
	}
} // namespace ft

#endif