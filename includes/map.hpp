/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:23:49 by rponsonn          #+#    #+#             */
/*   Updated: 2022/10/17 03:07:22 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP
#include <memory>//allocator
#include <exception>
//#include <map>
#include <functional>
#include <utility>
#include "pair.hpp"
#include "tree.hpp"
namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
		typedef Key														key_type;//
		typedef T														mapped_type;//
		typedef ft::pair<const key_type, mapped_type>					value_type;//
		typedef Compare													key_compare;//
		class value_compare : public std::binary_function<value_type, value_type, bool>//verify if this is legal or I should make my own
		{
			friend class map<Key, T, Compare, Alloc>
			protected:
			Compare	comp;
			value_compare(Compare c): comp(c) {}
			public:
			typedef bool	result_type;
			typedef value_type	first_argument_type;
			typedef value_type	second_argument_type;
			bool operator()(const_reference x, const_reference y)const//maybe map::const_reference?
			{ return comp(x.first, y.first);}
		};
		typedef Alloc													allocator_type;//
		typedef value_type&												reference;
		typedef const value_type&										const_reference;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;
		typedef typename ft::tree<value_type>::iterator					iterator;//need to include these in tree class
		typedef typename ft::tree<value_type>::const_iterator			const_iterator;
		typedef typename ft::tree<value_type>::reverse_iterator			reverse_iterator;
		typedef typename ft::tree<value_type>::const_reverse_iterator	const_reverse_iterator;
		typedef typename allocator_type::size_type						size_type;
		typedef typename allocator_type::difference_type				difference_type;
		private:
		allocator_type					_alloc;
		tree<value_type, value_compare>	_tree;
		key_compare						_key_comp;
		value_compare					_value_comp;//
		public:
		explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()): tree()
		{
			_key_comp = comp;
			_alloc = alloc;
			_value_comp = value_compare();//review if this is necessary
		}
		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
		{
			_key_comp = comp;
			_alloc = alloc;
			_value_comp = value_compare()
			//function to put all the values with 2 iterators;
		}
		map(const map &x)
		{
			_alloc = x._alloc;
			_tree = x._tree;
			_key_comp = x._key_comp;
			_value_comp = x._value_comp;
		}
		~map(void);
		map	&operator=(const map &x)
		{
			if (this != &x)
			{
				_alloc = x._alloc;
				_tree = x._tree;
				_key_comp = x._key_comp;
				_value_comp = x._value_comp;
			}
			return (*this);
		}
		iterator begin(void)
		{
			return (_tree.begin());
		}
		const_iterator begin(void)const
		{
			return (_tree.begin());
		}
		iterator end(void)
		{
			return (_tree.end());
		}
		const_iterator end(void)const
		{
			return (_tree.end());
		}
		reverse_iterator rbegin(void)
		{
			return (_tree.rbegin());
		}
		const_reverse_iterator rbegin(void)const
		{
			return (_tree.rbegin());
		}
		reverse_iterator rend(void)
		{
			return (_tree.rend());
		}
		const_reverse_iterator rend(void)const
		{
			return (_tree.rend());
		}
		bool	empty(void)const
		{
			return (_tree.begin() == _tree.end());
		}
		size_type	size(void)const
		{
			return (_tree.size());
		}
		size_type	max_size(void)const
		{
			return (_tree.max_size());
		}
		mapped_type	&operator[] (const key_type &k)
		{
			iterator i 
		}
	};
} // namespace ft

#endif