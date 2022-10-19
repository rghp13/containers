/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 13:10:34 by rponsonn          #+#    #+#             */
/*   Updated: 2022/10/19 03:06:05 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
# define TREE_HPP
#include <memory>
#include "map_iterator.hpp"
namespace ft
{
	template <class T>
	class node
	{
		public:
		typedef T	value_type;
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
		{
			if (this != &src)
			{
				parent = src.parent;
				left = src.left;
				right = src.right;
				data = src.data;
				height = src.height;
			}
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
	class tree
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
		typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
		//add iterators later
		private:
		pointer			_start;
		pointer			_end;
		size_type		_size;
		allocator_type	_alloc;
		key_comp		_comp;
		public:
		tree(const allocator_type &alloc = allocator_type(), const key_comp &comp = key_comp()): _alloc(alloc), _comp(comp), _start(0), _end(0), _size(0) {}
		~tree()
		{
			//write function to delete all nodes
		}
		//iterator functions to be taken from maps
		bool empty(void) const
		{
			return (_size == 0);
		}
		size_type size(void) const
		{
			return (_size);
		}
		size_type max_size()const
		{
			return (_alloc.max_size());
		}
		/*find(key_type &key)const
		{
			pointer ptr = _start;
			if (ptr == 0)
		}*/

		pointer	create_node(value_type &val)
		{
			pointer ptr = _alloc.allocate(1);
			_alloc.construct(ptr, node(val));
			_size++;
			return (ptr);
		}
		delete_node(pointer ptr)//update all the pointers before calling this
		{
			_alloc.destroy(ptr);
			_alloc.deallocate(ptr, 1);
			_size--;
		}
	};//left if smaller right if equal or bigger... which is what std::less does

} // namespace ft

#endif