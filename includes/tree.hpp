/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 13:10:34 by rponsonn          #+#    #+#             */
/*   Updated: 2022/10/31 02:51:53 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
# define TREE_HPP
#include <memory>
#include "map_iterator.hpp"
#include "map.hpp"
#include "reverse_iterator.hpp"
namespace ft
{

	//std::less == Function object for performing comparisons. Unless specialized, invokes operator< on type T
	//template <class T>
	template <class T, class compare >
	class tree
	{
		class node
		{
			public:
			typedef T		value_type;//this is typically the pair object
			typedef node*	node_pointer;
			private:
			node_pointer		parent;
			node_pointer		left;
			node_pointer		right;
			value_type	data;
			int height;
			public:
			node(const value_type &src, node_pointer parent = 0, node_pointer left = 0, node_pointer right = 0, int height = 1): data(src), parent(parent), left(left), right(right), height(height) {}
			node(const node &src)
			{
				*this = src;
			}
			~node() {}
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
			bool leaf_test(void)
			{
				return (!left && !right)
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
		public:
		typedef T																				value_type;//the pair object
		typedef typename node<T>																node_type;
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
		template <class Tt, bool isconst = false>
		class bidirectional_iterator : public ft::iterator<std::bidirectional_iterator_tag, T>
		{
			public:
			typedef Tt											value_type;
			typedef Tt&											reference;
			typedef Tt*											pointer;
			typedef std::bidirectional_iterator_tag				iterator_category;
			typedef ptrdiff_t									difference_type;

			typedef bidirectional_iterator<T>					self;
			typedef typename node::node_pointer					node_pointer;
			typedef ft::tree<value_type>*						tree_pointer;
			private:
			node_pointer	_ptr;
			node_pointer	_end;//parent == root, left == leftmost node, right equals rightmost node
			//construct
			bidirectional_iterator(): _ptr(0), _end(0) {}
			bidirectional_iterator(node_pointer src, node_pointer end): _ptr(src), _end(end) {}
			bidirectional_iterator(bidirectional_iterator const &src): _ptr(src._ptr), _end(src._end) {}
			~bidirectional_iterator() {}
			bidirectional_iterator &operator=(bidirectional_iterator const &x)
			{
				if (this != &x)
				{
					_ptr = x._ptr;
					_end = x._end;
				}
				return (*this);
			}
			reference				operator*()			{return(_ptr->value);}//use/include/c++/11/bits/stl_tree.h line 256
			pointer					operator->()		{return(&(_ptr->value));}
			bidirectional_iterator	&operator++()
			{
				if (_ptr == _end)//if out of bounds do nothing
					return (*this);
				else if (_ptr == _end->right)//if last node
					_ptr = _end;//move out of bounds
				else if (_ptr->right != 0)
				{
					_ptr = _ptr->right;
					while (_ptr->left != 0)
						_ptr = _ptr->left;
				}
				else
				{
					while (_ptr->parent && _ptr->parent->right == _ptr)
						_ptr = _ptr->parent;
					if (_ptr->parent)
						_ptr = _ptr->parent;
				}
				return (*this);
			}
			bidirectional_iterator operator++(int)
			{
				bidirectional_iterator tmp(_ptr);
				operator++();
				return (tmp);
			}
			bidirectional_iterator &operator--()
			{
				if (_ptr == _end)//if out of bounds
					_ptr = _end->right;//move to last element
				else if (_ptr == _end->left)//if left-most element
					_ptr = _end;//move out of bounds
				else if (_ptr->left)
				{
					_ptr = _ptr->left;
					while (_ptr->right)
						_ptr = _ptr->right;
				}
				else
				{
					while (_ptr->parent && _ptr->parent->left == _ptr)
						_ptr = _ptr->parent;
					if (_ptr->parent)
						_ptr = _ptr->parent;
				}
				return (*this);
			}
			bidirectional_iterator operator--(int)
			{
				bidirectional_iterator tmp(_ptr);
				operator--();
				return (tmp);
			}
			//needs == !=
			bool operator==(bidirectional_iterator<Tt, false> const &src)const
			{
				return (_ptr == src._ptr);
			}
			bool operator!=(bidirectional_iterator<Tt, false> const &src)const
			{
				return (_ptr != src._ptr);
			}
			bool operator==(bidirectional_iterator<Tt, true> const &src)const
			{
				return (_ptr == src._ptr);
			}
			bool operator!=(bidirectional_iterator<Tt, true> const &src)const
			{
				return (_ptr != src._ptr);
			}
		};
		typedef bidirectional_iterator<value_type>												iterator;
		typedef bidirectional_iterator<const value_type, true>									const_iterator;
		typedef typename ft::reverse_iterator<iterator>											reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>									const_reverse_iterator;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
		//add iterators later
		private:
		pointer			_start;//left most node
		pointer			_last;//right most node
		pointer			_end;//node that exists out of bounds
		pointer			_root;//uppermost node
		size_type		_size;
		allocator_type	_alloc;
		key_comp		_comp;//this is the value_compare class from map
		public:
		tree(const compare &comp): _alloc(allocator_type()), _comp(comp), _start(0), _last(0), _size(0), _root(0)
		{
			_end = _alloc.allocate(1);
			_alloc.construct(_end, value_type());//avoids incrementing size
		}
		tree(const tree &src): _alloc(src._alloc), _comp(src._comp), 
		{
			_end = _alloc.allocate(1);
			_alloc.construct(_end, value_type());
			//implement a recursive copy function that spreads from the root and doesn't balance because it's a straight copy;
			pointer ptr = src._root;
			non_balancing_copy(ptr);
			update_end_node();
		}
		~tree()
		{
			clear();
			_alloc.destroy(_end);//removes _end's node which isn't included in the clear()
			_alloc.deallocate(_end);
		}
		tree	&operator=(const tree &x)
		{
			if (this != &x)
			{
				clear();
				//implement a recursive copy function that spreads from the root and doesn't balance because it's a straight copy;
				non_balancing_copy(x._root);//remember this updates _root
				update_end_node();
			}
		}
		iterator	begin(void)//NOTE TO SELF Review behavior on empty tree
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
		private://internal functions for managing the binary tree
		void	update_end_node(void)//shouldn't be used if root is empty
		{
			pointer tmp;
			if (_size == 0)
			{
				_end->parent
			}
			if (!_root)
				return ;
			while (_root->parent)
				_root = _root->parent;
			_end->parent = _root;
			tmp = _root;
			while (tmp->left)
				tmp = tmp->left;
			end->left = tmp;
			tmp = _root;
			while (tmp->right)
				tmp = tmp->right;
			end->right = tmp;
		}
		void	_recursive_clear(pointer node)//pointer should not be null
		{
			if (node->left)
				_recursive_clear(node->left);
			if (node->right)
				_recursive_clear(node->right);
			delete_node(node);
		}
		ft::pair<iterator, bool> _internal_insert(const value_type &val)
		{
			iterator base = find(val);
			pointer search = _root;

			if (base != end())//value already exists
				return (ft::make_pair(base, false));
			if (_root == 0)
			{
				_root = create_node(val);
				return (ft::make_pair(iterator(_root), true));
			}
			while (true)
			{
				if (_comp(val.first, search->data.first))//if val is less than search go left
				{
					if (search->left)//left node exists
					{
						search = search->left;
						continue;
					}
					else//left doesn't exist
					{
						if (search->left == 0 && search->right)
						search->left = create_node(val);//create
						search->left->parent = search;
					}
				}
			}
		}
		bool	update_height(pointer node)//new nodes start at 1 empty is 0 returns if out of balance
		{
			int lh, rh, balance;
			if (node->left == 0)
				lh = 0;
			else
				lh = node->left->height;
			if (node->right == 0)
				rh = 0;
			else
				rh = node->right->height;
			node->height = (lh > rh) ? lh + 1 : rh + 1;//bigger number + 1 gets stored
			balance = lh - rh;
			if (balance < 0)
				balance *= -1;
			if (balance <= 1)
				return (false);//if balance is less than or equal to 1 then do nothing
			else
				return (true);//test what sort of rebalancing
		}
		void non_balancing_copy(pointer oldroot)//should never be null and should already be empty
		{
			pointer newroot = create_node(oldroot->data);
			_root = newroot;
			newroot->height = oldroot->height;
			if (newroot->left)
				newroot->left = recursive_non_balancing_copy(oldroot->left, newroot);
			if (newroot->right)
				newroot->right = recursive_non_balancing_copy(oldroot->right, newroot);
			//update_begin();
			//update_end();
		}
		pointer	recursive_non_balancing_copy(pointer oldtree, pointer parent)//neither should be null
		{
			pointer newnode = create_node(oldtree->data);
			newnode->parent = parent;
			newnode->height = oldtree->height;
			if (oldtree->left)
				newnode->left = recursive_non_balancing_copy(oldtree->left, newnode);
			if (oldtree->right)
				newnode->right = recursive_non_balancing_copy(oldtree->right, newnode);
			return (newnode);
		}
		void	update_begin(void)
		{
			pointer search = _root;
			if (_root)
			{
				while (search->left)
					search = search->left;
			}
			_start = search;
		}
		pointer	create_node(const value_type &val)//you still need to make the pointer connections
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