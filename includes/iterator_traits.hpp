/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 23:01:04 by rponsonn          #+#    #+#             */
/*   Updated: 2022/07/03 18:52:39 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP
#include <cstddef>

namespace ft
{
	struct	input_iterator_tag {};
	struct	output_iterator_tag {};
	struct	forward_iterator_tag : public input_iterator_tag {};
	struct	bidirectional_iterator_tag : public forward_iterator_tag {};
	struct	random_access_iterator_tag : public bidirectional_iterator_tag {};

	template<typename Category, class T, class Distance = ptrdiff_t,
			 typename _Pointer = T*, class _Refererence = T&>
	struct iterator
	{
		typedef	Category		iterator_category;
		typedef	T				value_type;
		typedef	Distance		difference_type;
		typedef	_Pointer		pointer;
		typedef	_Refererence	reference;
	};
	template<class Iterator>
	struct iterator_traits
	{
		typedef typename		Iterator::iterator_category	iterator_category;
		typedef typename		Iterator::value_type		value_type;
		typedef typename		Iterator::difference_type	difference_type;
		typedef typename		Iterator::pointer			pointer;
		typedef	typename		Iterator::reference			reference;
	};
	template <class _Tp>
	struct	iterator_traits<_Tp*>
	{
		typedef random_access_iterator_tag	iterator_category;
		typedef	_Tp							value_type;
		typedef	ptrdiff_t					difference_type;
		typedef	_Tp*						pointer;
		typedef	_Tp&						reference;
	};
	template <class _Tp>
	struct	iterator_traits<const _Tp*>
	{
		typedef random_access_iterator_tag	iterator_category;
		typedef	_Tp							value_type;
		typedef	ptrdiff_t					difference_type;
		typedef	const _Tp*					pointer;
		typedef	const _Tp&					reference;
	};
};
#endif
