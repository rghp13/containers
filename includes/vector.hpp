/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:48:59 by rponsonn          #+#    #+#             */
/*   Updated: 2022/05/26 01:43:37 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
#include <memory>//allocator
//must implement
//Vector
//Map
//Stack
namespace ft
{
	template <typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		public:
		typedef T								value_type;
		typedef Alloc							allocator_type;
		typedef typename allocator_type::reference		reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;//might need to add typename
		typedef typename allocator_type::const_pointer	const_pointer;
		typedef Viterator<value_type>			iterator;//change this
	};
}//namespace ft
#endif