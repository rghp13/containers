/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 19:41:29 by rponsonn          #+#    #+#             */
/*   Updated: 2022/10/29 03:04:43 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP
#include "iterator_traits.hpp"
#include "tree.hpp"

namespace ft
{//might remove all this
	/*template <class _BiTerator>
	class reverse_bidirectional_iterator
	{
		public:
			typedef typename iterator_traits<_BiTerator>::iterator_category	iterator_category;
			typedef typename iterator_traits<_BiTerator>::value_type		value_type;
			typedef typename iterator_traits<_BiTerator>::difference_type	difference_type;
			typedef typename iterator_traits<_BiTerator>::pointer			pointer;
			typedef typename ft::_Biterator::node_pointer					node_pointer;
			typedef typename ft::_Biterator::node_ref						node_ref;
			typedef	typename iterator_traits<_BiTerator>::reference			reference;
			typedef _BiTerator												iterator_type;
		protected:
			iterator_type current;
		public:
		//constructor
		reverse_bidirectional_iterator(): current(iterator_type()) {}
		explicit reverse_bidirectional_iterator(iterator_type it): current(it) {}
		reverse_bidirectional_iterator(const reverse_bidirectional_iterator<_BiTerator> &rev_it): current(rev_it.current) {}
		~reverse_bidirectional_iterator() {}
		reverse_bidirectional_iterator &operator=(const reverse_bidirectional_iterator<_BiTerator> &other)
		{
			current = other.current;
		}
		//function
		iterator_type	base()const
		{	return (current);}
		//operator * -> ++ --
		reference operator*()const
		{
			_BiTerator __tmp = current;
			return (*(--__tmp));
		}
		pointer operator->()const
		{
			return(&(operator*()));
		}
		reverse_bidirectional_iterator &operator++()
		{
			--current;
			return (*this);
		}
		reverse_bidirectional_iterator operator++(int)
		{
			reverse_bidirectional_iterator tmp = *this;
			--current;
			return (tmp);
		}
		reverse_bidirectional_iterator &operator--()
		{
			++current;
			return (*this);
		}
		reverse_bidirectional_iterator operator--(int)
		{
			reverse_bidirectional_iterator tmp = *this;
			++current;
			return (tmp);
		}
	};*/
}
#endif