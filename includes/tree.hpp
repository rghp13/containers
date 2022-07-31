/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 13:10:34 by rponsonn          #+#    #+#             */
/*   Updated: 2022/07/31 21:31:57 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
# define TREE_HPP
#include <memory>
namespace ft
{
	template <class T>
	class node
	{
		public:
		typedef T	value_type;
		private:
		node*		parent;
		node*		left;
		node*		right;
		value_type	data;
		unsigned int height;
		public:
		node(const value_type &src, node* parent, node* left = 0, node* right = 0, unsigned int height = 1) : value(src)parent(parent), left(left), right(right), height(height) {}
		node(const node &src)
		{
			*this = src;
		}
		~node(void) {}
		node &operator=(const node &src)//this isn't going to work by itself
		{//inbound pointers need to be updated
			if (*this == src)
				return (*this);
			parent = src.parent;
			left = src.left;
			right = src.right;
			data = src.data;
			height = src.height;
			return (*this)
		}
		swap(node &src)
		{//should inbound pointers be udpated here?
			if (*this == src)
				return ;
			node temp(*this);
			*this = src;
			src = temp;
		}
	};
	//std::less == Function object for performing comparisons. Unless specialized, invokes operator< on type T
	template <class T, class compare = std::less<T> >
	class Tree
	{
		public:
		typedef T											value_type;
		typedef node<T>										node_type;
		typedef T::first_type								key_type;
		typedef compare										key_comp;
		typedef std::allocator<node_type>					allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::difference_type	difference_type;
		//add iterators later
		private:
		pointer			_start;
		pointer			_end;
		size_type		_size;
		allocator_type	_alloc;
		key_comp		_comp;
		public:
		Tree(const allocator_type &alloc = allocator_type(), const key_comp &comp = key_comp()): _alloc(alloc), _comp(comp), _start(0), _end(0), _size(0) {}

	}//left if smaller right if equal or bigger... which is what std::less does
} // namespace ft

#endif