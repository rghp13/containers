/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 19:41:29 by rponsonn          #+#    #+#             */
/*   Updated: 2022/10/26 17:27:00 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP
#include "iterator_traits.hpp"

namespace ft
{
	template <class T>
	class bidirectional_iterator : public ft::iterator<std::bidirectional_iterator_tag, T>
	{
		public:
		typedef T											value_type;
		typedef T&											reference;
		typedef T*											pointer;
		typedef std::bidirectional_iterator_tag				iterator_category;
		typedef ptrdiff_t									difference_type;

		typedef bidirectional_iterator<T>					self;
		typedef typename ft::node::node_pointer				node_pointer;
		typedef ft::tree<value_type>*						tree_pointer;
		private:
		node_pointer	ptr;
		tree_pointer	tree;
		//construct
		bidirectional_iterator(): ptr(0), tree(0) {}
		bidirectional_iterator(node_pointer src, tree_pointer srctree): ptr(src), tree(srctree) {}
		bidirectional_iterator(bidirectional_iterator const &src): ptr(src.ptr), tree(src.tree) {}
		~bidirectional_iterator() {}
		bidirectional_iterator &operator=(bidirectional_iterator const &x)
		{
			if (this != &x)
			{
				ptr = x.ptr;
				tree = x.tree;
			}
			return (*this);
		}
		pointer					base(void) const	{return (&(ptr->value));}//Hey remember that dereferencing a iterator returns the pair and not the node
		reference				operator*()			{return(ptr->value);}//use/include/c++/11/bits/stl_tree.h line 256
		pointer					operator->()		{return(&(ptr->value));}
		bidirectional_iterator	&operator++()
		{
			if (!ptr)
			{
				*this = ;//try to get pointer to begin, not the iterator
			}
			else if (ptr->right != 0)
			{
				ptr = ptr->right;
				while (ptr->left != 0)
					ptr = ptr->left;
			}
			else
			{
				while (ptr->parent && ptr->parent->right == ptr)
					ptr = ptr->parent;
				if (ptr->parent)
					ptr = ptr->parent;
			}
			return (*this);
		}
		bidirectional_iterator operator++(int)
		{
			bidirectional_iterator tmp(ptr);
			operator++();
			return (tmp);
		}
		bidirectional_iterator &operator--()
		{
			tree_decrement(ptr);
			/*if (ptr->left)
			{
				ptr = ptr->left;
				while (ptr->right)
					ptr = ptr->right;
			}
			else
			{
				while (ptr->parent && ptr->parent->left == ptr)
					ptr = ptr->parent;
				if (ptr->parent)
					ptr = ptr->parent;
			}*/
			return (*this);
		}
		bidirectional_iterator operator--(int)
		{
			bidirectional_iterator tmp(ptr);
			operator--();
			return (tmp);
		}
		//needs == !=
	};
	template<class _IteratorL, class _IteratorR>
	bool operator==(_IteratorL const &lhs, _IteratorR const &rhs)
	{
		return (lhs.base() == rhs.base());
	} 
	template<class _IteratorL, class _IteratorR>
	bool operator!=(_IteratorL const &lhs, _IteratorR const &rhs)
	{
		return (lhs.base() != rhs.base());
	}
	template <class _BiTerator>
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
	};
}
#endif