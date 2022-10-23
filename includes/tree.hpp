/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 13:10:34 by rponsonn          #+#    #+#             */
/*   Updated: 2022/10/23 03:25:23 by rponsonn         ###   ########.fr       */
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
		typedef T	value_type;//this is typically the pair object
		node*		parent;
		node*		left;
		node*		right;
		value_type	data;
		unsigned int height;
		public:
		node(const value_type &src, node* parent = 0, node* left = 0, node* right = 0, unsigned int height = 0) : value(src)parent(parent), left(left), right(right), height(height) {}
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
		void swap(node &src)//whats the end goal? complete swap does nothing, maybe you just want to swap the data?
		{
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
		typedef T																				value_type;//the pair object
		typedef node<T>																			node_type;
		typedef typename T::first_type															key_type;//added typename
		typedef typename T::second_type															mapped_type;//you might not need this, leave it to map to return the value
		typedef compare																			key_comp;
		typedef std::allocator<node_type>														allocator_type;//the allocator is tailored to the node
		typedef typename allocator_type::reference												reference;//node referrences
		typedef typename allocator_type::const_reference										const_reference;
		typedef typename allocator_type::pointer												pointer;//points to nodes
		typedef typename allocator_type::const_pointer											const_pointer;
		typedef typename allocator_type::size_type												size_type;
		typedef typename allocator_type::difference_type										difference_type;
		typedef typename ft::bidirectional_iterator<node_type>									iterator;
		typedef typename ft::bidirectional_iterator<const node_type>							const_iterator;
		typedef typename ft::reverse_bidirectional_iterator<iterator>							reverse_iterator;
		typedef typename ft::reverse_bidirectional_iterator<const_iterator>						const_reverse_iterator;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
		//add iterators later
		private:
		pointer			_start;
		pointer			_end;
		pointer			_root;
		size_type		_size;
		allocator_type	_alloc;
		key_comp		_comp;//this is the value_compare class from map
		public:
		tree(void): _alloc(), _comp(), _start(0), _end(0), _size(0), _root(0) {}
		tree(const tree &src): _alloc(src._alloc), _comp(src._comp), 
		{
			//implement a recursive copy function that spreads from the root and doesn't balance because it's a straight copy;
		}
		~tree()
		{
			clear();
		}
		tree	&operator=(const tree &x)
		{
			if (this != &x)
			{
				clear();
				//implement a recursive copy function that spreads from the root and doesn't balance because it's a straight copy;
			}
		}
		iterator	begin(void)//REMEMBER TO REVIEW HOW ITERATOR MOVEMENT WORKS
		{
			return (iterator(_start));
		}
		const_iterator	begin(void)const
		{
			return(const_iterator(_start));
		}
		iterator	end(void)
		{
			return (iterator(_end))
		}
		const_iterator	end(void)const
		{
			return (const_iterator(_end));
		}
		reverse_iterator rbegin(void)
		{
			return (reverse_iterator(end()));
		}
		const_reverse_iterator rbegin(void)const
		{
			return (const_reverse_iterator(end()));
		}
		reverse_iterator	rend(void)
		{
			return (reverse_iterator(begin()));
		}
		const_reverse_iterator	rend(void)const
		{
			return (const_reverse_iterator(begin()));
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
		//insert rules add new nodes, however if key already exists do not add or update, return iterator to found object
		ft::pair<iterator, bool> insert(const value_type &val)
		{
			return (_internal_insert(val));
		}
		private:
		ft::pair<iterator, bool> _internal_insert(const value_type &val)
		{
			iterator base = find(val);
			if (base != end())//value already exists|| What if root of tree is null? that's not a problem
				return (ft::make_pair(base, false));
			base.ptr = root;
		}
		pointer	create_node(value_type &val)//you still need to make the pointer connections
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