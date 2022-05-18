/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:07:06 by rponsonn          #+#    #+#             */
/*   Updated: 2022/05/18 22:18:01 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP
#include <vector>
namespace ft
{
	template <typename T, typename Container = std::vector<T> >
	class stack
	{
		public:
		typedef T value_type;
		typedef Container container_type;
		typedef size_t	size_type;
	//constructors
	explicit	stack(const container_type &ctnr = container_type())
	{
		_ctnr = ctnr;
	}
				stack(const stack	&other);
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
		protected:
		container_type _ctnr;
	};
} // namespace ft

#endif