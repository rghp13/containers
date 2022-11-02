/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:23:49 by rponsonn          #+#    #+#             */
/*   Updated: 2022/11/01 21:19:25 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP
#include <memory>//allocator
#include <exception>
#include <stdexcept>
//#include <map>
#include <functional>
#include <utility>
#include "pair.hpp"
#include "make_pair.hpp"
#include "tree.hpp"
#include "equal.hpp"
#include "lexicographical_compare.hpp"
namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
		typedef Key														key_type;//
		typedef T														mapped_type;//
		typedef ft::pair<const key_type, mapped_type>					value_type;//the pair
		typedef Compare													key_compare;//
		class value_compare : public std::binary_function<value_type, value_type, bool>//verify if this is legal or I should make my own
		{
			//friend class map<Key, T, Compare, Alloc>;
			protected:
			key_compare	comp;
			value_compare(key_compare c): comp(c) {}
			value_compare(const value_compare &src): comp(src.comp) {}//added for copy construction
			public:
			typedef bool	result_type;
			typedef value_type	first_argument_type;
			typedef value_type	second_argument_type;
			bool operator()(const_reference x, const_reference y)const//the pair itself is needed not the node
			{
				return comp(x.first, y.first);//returns true if x is smaller
			}
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
		explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
		{
			_key_comp = comp;
			_alloc = alloc;
			_value_comp = value_compare(_key_comp);
			_tree(_value_comp,)
		}
		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
		{
			_key_comp = comp;
			_alloc = alloc;
			_value_comp = value_compare();
			insert(first, last);
		}
		map(const map &x)
		{
			_alloc = x._alloc;
			_key_comp = x._key_comp;
			_value_comp = x._value_comp;
			_tree = x._tree;
		}
		~map(void){}
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
			return (_tree.empty());
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
			insert();//find node, if it exists return the value if it doesn't exist create one and return value
		}
		mapped_type	&at(const key_type &key)
		{
			//find node if it doesn't exist throw
			;//throw std::out_of_range("map::at");
		}
		const mapped_type	&at(const key_type &key)const
		{
			;//same as previous function
		}
		ft::pair<iterator, bool>	insert(const value_type &value)
		{
			return (_tree.insert(value));
		}
		iterator	insert(iterator position, const value_type &val)
		{
			(void)position;
			return (_tree.insert(val));//hint disregarded
		}
		template <class InputIterator>
		void		insert(InputIterator first, InputIterator last)
		{
			while (first != last)
				_tree.insert(first++);
		}
		void		erase(iterator position)
		 {//References and iterators to the erased elements are invalidated. Other references and iterators are not
			_tree.erase(position);
		}
		size_type	erase(const key_type &k)
		{
			return (_tree.erase(k));
		}
		void		erase(iterator first, iterator last)//the range does not include the last iterator
		{
			while (first != last)
				_tree.erase(first++);
		}
		void	swap(map &x)
		{
			std::swap(_alloc, x._alloc);
			std::swap(_key_comp, x._key_comp);
			std::swap(_value_comp, x._value_comp);
			_tree.swap(x._tree);
		}
		void	clear(void)
		{
			_tree.clear();
		}
		key_compare	key_comp(void)const
		{
			return (_key_comp);
		}
		value_compare	value_comp(void)const
		{
			return (_value_comp);
		}
		iterator		find(const key_type &k)
		{
			return (_tree.find(ft::make_pair(k, mapped_type())));//consider updating the tree find function
		}
		const_iterator	find(const key_type &k)const
		{
			return (_tree.find(ft::make_pair(k, mapped_type())));
		}//count equal range lower bound upperbound
		size_type		count(const key_type &k)const
		{
			const_iterator it = find(ft::make_pair(k, mapped_type());
			return ((it != end()));
		}
		iterator		lower_bound(const key_type &k)
		{
			return (_tree.lower_bound(ft::make_pair(k, mapped_type()));
		}
		const_iterator	lower_bound(const key_type &k)const
		{
			return (_tree.lower_bound(ft::make_pair(k, mapped_type()));
		}
		iterator		upper_bound(const key_type &k)
		{
			return (_tree.upper_bound(ft::make_pair(k, mapped_type()));
		}
		const_iterator	upper_bound(const key_type &k)
		{
			return (_tree.upper_bound(ft::make_pair(k, mapped_type()));
		}
		pair<const_iterator,const_iterator>	equal_range(const key_type &k)const
		{
			return (_tree.equal_range(ft::make_pair(k, mapped_type())));
		}
		pair<iterator, iterator>			equal_range(const key_type)
		{
			return (_tree.equal_range(ft::make_pair(k, mapped_type())));
		}
		allocator_type	get_allocator(void)const
		{
			return (_alloc);
		}
	};
	template < class Key, class T, class Compare, class Alloc >
	void swap(ft::map<Key, T, Compare, Alloc> &lhs, ft::map<Key, T, Compare, Alloc> &rhs)
	{
		lhs.swap(rhs);
	}
	template < class Key, class T, class Compare, class Alloc >
	bool operator==(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
	{//check size first then do lexicographical comparisons
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	template < class Key, class T, class Compare, class Alloc >
	bool operator!=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}
	template < class Key, class T, class Compare, class Alloc >
	bool operator<(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template < class Key, class T, class Compare, class Alloc >
	bool operator<=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return (lhs == rhs || lhs < rhs);
	}
	template < class Key, class T, class Compare, class Alloc >
	bool operator>(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return (rhs < lhs);
	}
	template < class Key, class T, class Compare, class Alloc >
	bool operator>=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return (lhs == rhs || rhs < lhs);
	}
} // namespace ft

#endif