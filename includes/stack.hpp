/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:07:06 by rponsonn          #+#    #+#             */
/*   Updated: 2022/05/17 18:14:36 by rponsonn         ###   ########.fr       */
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
	explicit	stack(const container_type &ctnr = container_type());
				stack(const stack	&other);
		private:
		container_type _ctnr;
	};
} // namespace ft

#endif