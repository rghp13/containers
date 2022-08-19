/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:23:49 by rponsonn          #+#    #+#             */
/*   Updated: 2022/08/12 15:53:29 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP
#include <memory>//allocator
#include <exception>
#include <functional>
#include <utility>
#include "pair.hpp"
namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		typedef Key														key_type;//
		typedef T														mapped_type;//
		typedef Alloc													allocator_type;//
		typedef ft::pair<const key_type, mapped_type>					value_type;//
		typedef typename allocator_type::size_type						size_type;
		typedef typename allocator_type::difference_type				difference_type;
		typedef Compare													key_compare;//

		typedef value_type&												reference;
		typedef const value_type&										const_reference;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;
		typedef typename ft::tree<value_type>::iterator					iterator;//need to include these in tree class
		typedef typename ft::tree<value_type>::const_iterator			const_iterator;
		typedef typename ft::tree<value_type>::reverse_iterator			reverse_iterator;
		typedef typename ft::tree<value_type>::const_reverse_iterator	const_reverse_iterator;

		class value_compare : public std::binary_function<value_type, value_type, bool>//verify if this is legal or I should make my own
		{
			friend class map<Key, T, Compare, Alloc>
			protected:
			Compare	comp;
			value_compare(Compare c): comp(c) {}
			public:
			bool operator()(const_reference x, const_reference y)const//maybe map::const_reference?
			{ return comp(x.first, y.first);}
		};

	};
} // namespace ft

#endif