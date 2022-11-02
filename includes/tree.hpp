/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 13:10:34 by rponsonn          #+#    #+#             */
/*   Updated: 2022/11/02 17:47:07 by rponsonn         ###   ########.fr       */
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
	//AVL pros and cons vs RB + great if frequent search and not many insertions
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
			node &operator=(const node &src)//this is taking all the pointers from src
			{
				if (this != &src)
				{
					parent = src.parent;
					if (parent)
					{
						if (parent->left == &src)
							parent->left = this;
						else if (parent->right == &src)
					}
					left = src.left;
					right = src.right;
					//data = src.data;don't transfer pair
					height = src.height;
				}
				return (*this)
			}
			bool leaf_test(void)
			{
				return (!left && !right)
			}
			int get_height(node_pointer const src)
			{
				if (!src)
					return (0);
				return (src->height);
			}
			void swap(node &src)//whats the end goal? complete swap does nothing, maybe you just want to swap the data?
			{//only use is maybe if you want to move it to a new tree but the pointers still point to the old tree's data
				if (this == &src)
					return ;
				pointer tmpl = left;
				pointer tmpr = right;//updating my left and right
				pointer tmpp = parent;
				if (src.left == this)//if im to the left
					left = &src;//then it has to go to my left
				else
					left = src.left;
				if (src.right == this)
					right = &src;
				else
					right = src.right;
				if (left)//updated left needs to set itself as parent to subnode
					left->parent = this;
				if (right)
					right->parent = this;
				//updating src's left and right
				if (tmpl == &src)
					src.left = this;
				else
					src.left = tmpl;
				if (tmpr == &src)
					src.right = this;
				else
					src.right = tmpr;
				if (tmpl)
					tmpl->parent = &src;
				if (tmpr)
					tmpr->parent = &src;
				//updating my parent
				if (src.parent == this)
					parent = &src;
				else
					parent = src.parent;
				if (parent)
				{
					if (parent->left == &src)
						parent->left = this;
					else if (parent->right == &src)
						parent->right = this;
				}
				//updating their parent
				src.parent = tmpp;
				if (src.parent)
				{
					if (src.parent->left == this)
						src.parent->left = &src;
					else if (src.parent->right == this)
						src.parent->right = &src;
				}
				std::swap(height, src.height);
				//do I want to swap the key-val pair?
				//A is being deleted and B is taking its spot
				//B swaps all A's pointers and height
				//swapping data wouldn't be helpful
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
			protected:
			node_pointer	_ptr;
			node_pointer	_sentinel;//points to sentinel, parent == root, left == leftmost node, right equals rightmost node
			//construct
			public:
			bidirectional_iterator(): _ptr(0), _sentinel(0) {}
			bidirectional_iterator(node_pointer src, node_pointer end): _ptr(src), _sentinel(end) {}
			bidirectional_iterator(bidirectional_iterator const &src): _ptr(src._ptr), _sentinel(src._sentinel) {}
			~bidirectional_iterator() {}
			bidirectional_iterator &operator=(bidirectional_iterator const &x)
			{
				if (this != &x)
				{
					_ptr = x._ptr;
					_sentinel = x._sentinel;
				}
				return (*this);
			}
			reference				operator*()			{return(_ptr->value);}//use/include/c++/11/bits/stl_tree.h line 256
			pointer					operator->()		{return(&(_ptr->value));}
			bidirectional_iterator	&operator++()
			{
				if (_ptr == _sentinel)//if out of bounds do nothing
					return (*this);
				else if (_ptr == _sentinel->right)//if last node
					_ptr = _sentinel;//move out of bounds
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
				bidirectional_iterator tmp(_ptr, _sentinel);
				operator++();
				return (tmp);
			}
			bidirectional_iterator &operator--()
			{
				if (_ptr == _sentinel)//if out of bounds
					_ptr = _sentinel->right;//move to last element
				else if (_ptr == _sentinel->left)//if left-most element
					_ptr = _sentinel;//move out of bounds
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
				bidirectional_iterator tmp(_ptr, _sentinel);
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
		pointer			_sentinel;//node that exists out of bounds
		pointer			_last_inserted;
		pointer			_root;//uppermost node
		size_type		_size;
		allocator_type	_alloc;
		key_comp		_comp;//this is the value_compare class from map
		public:
		tree(const compare &comp): _alloc(allocator_type()), _comp(comp), _start(0), _last(0), _size(0), _root(0)
		{
			_sentinel = _alloc.allocate(1);
			_alloc.construct(_sentinel, value_type());//avoids incrementing size
		}
		tree(const tree &src): _alloc(src._alloc), _comp(src._comp), 
		{
			_sentinel = _alloc.allocate(1);
			_alloc.construct(_sentinel, value_type());
			//implement a recursive copy function that spreads from the root and doesn't balance because it's a straight copy;
			pointer ptr = src._root;
			non_balancing_copy(ptr);
			update_sentinel_node();
		}
		~tree()
		{
			clear();
			_alloc.destroy(_sentinel);//removes _sentinel's node which isn't included in the clear()
			_alloc.deallocate(_sentinel);
		}
		tree	&operator=(const tree &x)
		{
			if (this != &x)
			{
				clear();
				//implement a recursive copy function that spreads from the root and doesn't balance because it's a straight copy;
				non_balancing_copy(x._root);//remember this updates _root
				update_sentinel_node();
			}
		}
		  //////////////////////////////////////////////////////////////////
		 /////////////////////////ITERATORS////////////////////////////////
		//////////////////////////////////////////////////////////////////
		iterator	begin(void)//NOTE TO SELF Review behavior on empty tree
		{
			if (_root)
				return (iterator(_start, _sentinel));
			return (end());
		}
		const_iterator	begin(void)const
		{
			if (_root)
				return(const_iterator(_start, _sentinel));
			return (end());
		}
		iterator	end(void)
		{
			return (iterator(_sentinel ,_sentinel))
		}
		const_iterator	end(void)const
		{
			return (const_iterator(_sentinel, _sentinel));
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
		  //////////////////////////////////////////////////////////////////
		 /////////////////////////////Capacity/////////////////////////////
		//////////////////////////////////////////////////////////////////
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
		  //////////////////////////////////////////////////////////////////
		 ////////////////////////////Modifiers/////////////////////////////
		//////////////////////////////////////////////////////////////////
		//insert rules add new nodes, however if key already exists do not add or update, return iterator to found object
		ft::pair<iterator, bool> insert(const value_type &val)
		{
			iterator tmp = find(val);
			if (tmp == end())//could not be found
			{
				_internal_insert(_root, val);
				return (ft::make_pair(iterator(_last_inserted, _sentinel), true));
			}
			return (ft::make_pair(tmp, false));
		}
		size_type	erase(key_type const &key)
		{//unsure if i can access protected variable from nested class
			
		}
		private://internal functions for managing the binary tree
		pointer	recursive_internal_delete(pointer node, const key_type &key)
		{
			pointer	tmp;
			int		balance;
			if (!node)
				return (node);//in case you can't find it
			if (_comp(key, node->data.first))//key is less go left
			{
				node->left = recursive_internal_delete(node->left, key);
				if (node->left)//if this isn't replaced with a null set new parent
					node->left->parent = node;
			}
			else if ((_comp(node->data.first, key)))//can't do !_comp because it would catch ==
			{
				node->right = recursive_internal_delete(node->right, key);
				if (node->right)
					node->right->parent = node;
			}
			else//this is the node to delete
			{
				if (node->left == 0 || node->right == 0)//if one or both child is empty
				{
					tmp = node->left ? node->left: node->right;//if left is valid store it otherwise go right
					if (!tmp)//no child
					{
						delete_node(node);
						return (0);
					}
					else//tmp is equal to the 1 child
					{
						delete_node(node);
						return (tmp);//doesn't need heigh re-adjustment
					}
				}
				else//2 children
				{//geeks says to take smallest value on the right
					tmp = node->right;
					while (tmp->left)
						tmp = tmp->left;
					node->swap(*tmp);//tmp node now becomes upper node but keeps key/value
					std::swap(node, tmp);//node pointer now points to the higher node
					node->right = recursive_internal_delete(node->right, key);//should still find the correct key
					if (node->right)//setting parent
						node->right->parent = node;
				}
			}
			//check for height and rebalances
			balance = update_height(node);
			//LL
			if (balance > 1 && update_height(node->left))
		}
		//Rotations
		//https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
		pointer	right_rotate(pointer y)//should not be null rotates left to the right
		{
			pointer x = y->left;
			pointer t2 = x->right;
			//rotate
			x->right = y;
			y->left = t2;
			if (t2)
				t2->parent = y;
			x->parent = y->parent;
			y->parent = x;
			update_height(y);//update y first because it's now lower
			update_height(x);
			if (_root == y)
			{
				_root = x;
			}
			return (x);
		}
		//rotate subtree rooted with x
		//LL case is a right rotate
		//LR is a left subtree left rotate then main right rotate
		//RR is a left rotate
		pointer	left_rotate(pointer x)
		{
			pointer y = x->right;
			pointer t2 = y->left;
			//rotate
			y->left = x;
			x->right = t2;
			if (t2)
				t2->parent = x;
			y->parent = x->parent;
			x->parent = y;
			update_height(x);
			update_height(y);
			if (_root == x)
				_root = y;
			return (y);
		}
		void	update_sentinel_node(void)
		{
			pointer tmp;
			if (_size == 0)//maybe if it was cleared
			{
				_sentinel->parent = 0;
				_sentinel->left = 0;
				_sentinel->right = 0;
				return;
			}
			while (_root->parent)
				_root = _root->parent;
			_sentinel->parent = _root;
			tmp = _root;
			while (tmp->left)
				tmp = tmp->left;
			end->left = tmp;
			_start = tmp;
			tmp = _root;
			while (tmp->right)
				tmp = tmp->right;
			end->right = tmp;
			_last = tmp;
		}
		void	_recursive_clear(pointer node)//pointer should not be null
		{
			if (node->left)
				_recursive_clear(node->left);
			if (node->right)
				_recursive_clear(node->right);
			delete_node(node);
		}
		pointer	_internal_insert(pointer node, const value_type &val)//already checked for duplicates
		{// THINK does newnode have a parent
			int balance;
			if (node == 0)
				return (_last_inserted = create_node(val));//lets me unwind recurse while keeping pointer of new node
			if (_comp(val.first, node->data.first))//if val is less than search go left
			{
				node->left = _internal_insert(node->left, val);
				node->left->parent = node;//makes sure parent is set
			}
			else
			{
				node->right = _internal_insert(node->right, val);
				node->right->parent = node;//make sure parent is set
			}
			balance = update_height(node);
			//LL
			if (balance > 1 && _comp(val.first,node->data.first))//if out of balance and val is smaller
				return (right_rotate(node));
			else if (balance > 1 && !(_comp(val.first, node->data.first)))//LR
			{
				node->left = left_rotate(node->left);
				return (right_rotate(node));
			}
			else if (balance < -1 && !(_comp(val.first, node->right->data.first)))//RR
				return (left_rotate(node));
			else if (balance < -1 && _comp(val.first, node->right->data.first))//RL
			{
				node->right = right_rotate(node->right);
				return (left_rotate(node));
			}
			return (node)//if no rotate return unchanged pointer
		}
		int	update_height(pointer node)//new nodes start at 1 empty is 0 returns if out of balance
		{//also returns balance
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
			return (balance);
		}
		void non_balancing_copy(pointer oldroot)//should never be null and should already be empty
		{
			pointer newroot = create_node(oldroot->data);
			_root = newroot;
			newroot->height = oldroot->height;
			if (newroot->left)
				newroot->left = recursive_non_balancing_copy(oldroot->left, newroot);//make sure that parents are correct
			if (newroot->right)
				newroot->right = recursive_non_balancing_copy(oldroot->right, newroot);
			update_sentinel_node();
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