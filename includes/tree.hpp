/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 13:10:34 by rponsonn          #+#    #+#             */
/*   Updated: 2022/11/17 20:45:31 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
# define TREE_HPP
#include <memory>
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
		template <class T1>
		class node
		{
			public:
			typedef T1		value_type;//this is typically the pair object
			typedef node*	node_pointer;
			//private:
			value_type	data;
			node_pointer		parent;
			node_pointer		left;
			node_pointer		right;
			int height;
			//public:
			node(const value_type &src, node_pointer parent = 0, node_pointer left = 0, node_pointer right = 0, int height = 1): data(src), parent(parent), left(left), right(right), height(height) {}
			/*node(const node &src)
			{
				*this = src;
			}*/
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
							parent->right = this;
					}
					left = src.left;
					right = src.right;
					data = src.data;
					height = src.height;
				}
				return (*this);
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
				//std::swap(data, src.data);
				//do I want to swap the key-val pair?
				//A is being deleted and B is taking its spot
				//B swaps all A's pointers and height
				//swapping data wouldn't be helpful
			}
		};
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
		template <class Tt, bool isconst = false>
		class bidirectional_iterator : public ft::iterator<std::bidirectional_iterator_tag, T>
		{
			public:
			typedef Tt											value_type;
			typedef Tt&											reference;
			typedef const Tt&									const_reference;
			typedef const Tt*									const_pointer;
			typedef Tt*											pointer;
			typedef std::bidirectional_iterator_tag				iterator_category;
			typedef ptrdiff_t									difference_type;

			//typedef typename node<Tt>::node_pointer					node_pointer;
			typedef	typename tree::node_type							node_type;
			typedef node_type*											node_pointer;
			protected:
			node_pointer	_ptr;
			node_pointer	_sentinel;//points to sentinel, parent == root, left == leftmost node, right equals rightmost node
			//construct
			public:
			bidirectional_iterator(): _ptr(0), _sentinel(0) {}
			bidirectional_iterator(node_pointer src, node_pointer sentinel): _ptr(src), _sentinel(sentinel) {}
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
			reference				operator*()			{return(_ptr->data);}
			const_reference			operator*()const	{return(_ptr->data);}
			pointer					operator->()		{return(&_ptr->data);}
			const_pointer					operator->()const	{return(&_ptr->data);}
			operator bidirectional_iterator<const Tt, true>()//conversion from non-const to const
			{
				return (bidirectional_iterator<const Tt, true>(_ptr, _sentinel));
			}
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
			bool operator==(bidirectional_iterator<const Tt, true> const &src)const
			{
				return (_ptr == src._ptr);
			}
			bool operator!=(bidirectional_iterator<const Tt, true> const &src)const
			{
				return (_ptr != src._ptr);
			}
		};
		typedef bidirectional_iterator<value_type, false>										iterator;
		typedef bidirectional_iterator<const value_type, true>									const_iterator;
		typedef typename ft::reverse_iterator<iterator>											reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>									const_reverse_iterator;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
		//add iterators later
		private:
		allocator_type	_alloc;
		key_comp		_comp;//this is the value_compare class from map
		pointer			_start;//left most node
		pointer			_last;//right most node
		pointer			_sentinel;//node that exists out of bounds
		pointer			_last_inserted;
		pointer			_root;//uppermost node
		size_type		_size;
		public:
		tree(const compare &comp): _alloc(allocator_type()), _comp(comp), _start(0), _last(0), _root(0), _size(0)
		{
			_sentinel = _alloc.allocate(1);
			_alloc.construct(_sentinel, value_type());//avoids incrementing size
		}
		tree(const tree &src): _alloc(src._alloc), _comp(src._comp), _start(0), _last(0), _root(0), _size(0)
		{
			_sentinel = _alloc.allocate(1);
			_alloc.construct(_sentinel, value_type());
			//implement a recursive copy function that spreads from the root and doesn't balance because it's a straight copy;
			pointer ptr = src._root;
			if (ptr)
				non_balancing_copy(ptr);
			update_sentinel_node();
		}
		~tree()
		{
			clear();
			_alloc.destroy(_sentinel);//removes _sentinel's node which isn't included in the clear()
			_alloc.deallocate(_sentinel, 1);
		}
		tree	&operator=(const tree &x)
		{
			if (this != &x)
			{
				clear();
				//implement a recursive copy function that spreads from the root and doesn't balance because it's a straight copy;
				if (x._root)
					non_balancing_copy(x._root);//remember this updates _root
				update_sentinel_node();
			}
			return (*this);
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
			return (iterator(_sentinel ,_sentinel));
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
		 ////////////////////////////Element_Access////////////////////////
		//////////////////////////////////////////////////////////////////
		
		  //////////////////////////////////////////////////////////////////
		 ////////////////////////////Modifiers/////////////////////////////
		//////////////////////////////////////////////////////////////////
		void clear(void)
		{
			_recursive_clear(_root);
			_root = 0;
			update_sentinel_node();
		}
		
		//insert rules add new nodes, however if key already exists do not add or update, return iterator to found object
		ft::pair<iterator, bool> insert(const value_type &val)//value type is fine for insertion
		{
			iterator tmp = find(val);
			if (tmp == end())//could not be found
			{
				_internal_insert(_root, val);
				if (!_root)
					_root = _last_inserted;
				update_sentinel_node();
				return (ft::make_pair(iterator(_last_inserted, _sentinel), true));
			}
			return (ft::make_pair(tmp, false));
		}
		size_type	erase(value_type const &val)
		{
			int pre,post;
			pre = _size;
			_root = recursive_internal_delete(_root, val);//should return root unless root was deleted
			if (_root && _root->parent)
				_root->parent = 0;
			update_sentinel_node();
			post = _size;
			if (post == pre)
				return (0);
			else
				return (1);
		}
		void	swap(tree &x)
		{
			std::swap(_comp, x._comp);
			std::swap(_alloc, x._alloc);
			std::swap(_size, x._size);
			std::swap(_root, x._root);
			std::swap(_sentinel, x._sentinel);
			std::swap(_start, x._start);
			std::swap(_last, x._last);
		}
		  //////////////////////////////////////////////////////////////////
		 ///////////////////////////Operations/////////////////////////////
		//////////////////////////////////////////////////////////////////
		iterator find(const value_type &k)
		{
			pointer search = _root;
			while (search)//valid node
			{
				if (search->data.first == k.first)//check for match
					return (iterator(search, _sentinel));
				if (_comp(k, search->data))//reminder, less than
					search = search->left;
				else
					search = search->right;
			}
			//failed to find
			return (end());
		}
		const_iterator find(const value_type &k)const
		{
			pointer search = _root;
			while (search)//valid node
			{
				if (search->data.first == k.first)//check for match
					return (const_iterator(search, _sentinel));
				if (_comp(k, search->data))//reminder, less than
					search = search->left;
				else
					search = search->right;
			}
			//failed to find
			return (end());
		}
		iterator	lower_bound(const value_type &val)
		{
			for (iterator it = begin(); it != end(); it++)
			{
				if (!_comp(*it, val))
					return (it);
			}
			return (end());
		}
		const_iterator	lower_bound(const value_type &val)const
		{
			for (const_iterator it = begin(); it != end(); it++)
			{
				if (!_comp(*it, val))
					return (it);
			}
			return (end());
		}
		iterator	upper_bound(const value_type &val)//10
		{
			for (iterator it = begin(); it != end(); it++)//1
			{
				if (_comp(val, *it))//1 < 10 which means 10 is greater than
					return (it);
			}
			return (end());
		}
		const_iterator	upper_bound(const value_type &val)const
		{
			for (const_iterator it = begin(); it != end(); it++)
			{
				if (_comp(val, *it))
					return (it);
			}
			return (end());
		}
		ft::pair<iterator, iterator> equal_range(const value_type &val)
		{
			return (ft::make_pair(lower_bound(val), upper_bound(val)));
		}
		ft::pair<const_iterator, const_iterator> equal_range(const value_type &val)const
		{
			return (ft::make_pair(lower_bound(val), upper_bound(val)));
		}
		  //////////////////////////////////////////////////////////////////
		 /////////////////////////Private_Internal/////////////////////////
		//////////////////////////////////////////////////////////////////
		private://internal functions for managing the binary tree
		pointer	recursive_internal_delete(pointer node, const value_type &val)
		{//step 1 find node
			pointer	tmp;
			int		balance;
			if (!node)
				return (node);//in case you can't find it
			if (_comp(val, node->data))//val is less go left
			{
				node->left = recursive_internal_delete(node->left, val);
				if (node->left)//if this isn't replaced with a null set new parent
					node->left->parent = node;
			}
			else if ((_comp(node->data, val)))//can't do !_comp because it would catch ==
			{
				node->right = recursive_internal_delete(node->right, val);
				if (node->right)
					node->right->parent = node;
			}
			else//Found node
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
					node->swap(*tmp);//tmp node now becomes upper node but keeps val/value
					//std::swap(node->data, tmp->data);//undoes swapping of data maybe it's best not to touch the data
					std::swap(node, tmp);//node pointer now points to the higher node
					node->right = recursive_internal_delete(node->right, val);//should still find the correct val
					if (node->right)//setting parent
						node->right->parent = node;
				}
			}
			//check for height and rebalances
			balance = update_height(node);
			//LL
			if (balance > 1)
			{
				if (update_height(node->left) >= 0)
					return (right_rotate(node));
				else if (update_height(node->left) < 0)//LR
				{
					node->left = left_rotate(node->left);
					return (right_rotate(node));
				}
			}
			if (balance < -1)
			{
				if (update_height(node->right) <= 0)//RR
					return (left_rotate(node));
				else if (update_height(node->right) > 0)//RL
				{
					node->right = right_rotate(node->right);
					return (left_rotate(node));
				}
			}
			return (node);//nothing to rebalance
		}
		//Rotations
		//https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
		pointer	right_rotate(pointer y)//should not be null rotates left to the right
		{
			pointer x = y->left;//left was null right was height of 4
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
		{//updates sentinel and _start _last
			pointer tmp;
			if (_size == 0 || _root == 0)//maybe if it was cleared
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
			_sentinel->left = tmp;
			_start = tmp;
			tmp = _root;
			while (tmp->right)
				tmp = tmp->right;
			_sentinel->right = tmp;
			_last = tmp;
		}
		void	_recursive_clear(pointer node)//pointer should not be null
		{
			if (node)
			{
				if (node->left)
					_recursive_clear(node->left);
				if (node->right)
					_recursive_clear(node->right);
				delete_node(node);
			}
		}
		pointer	_internal_insert(pointer node, const value_type &val)//already checked for duplicates
		{// THINK does newnode have a parent
			int balance;
			if (node == 0)
				return (_last_inserted = create_node(val));//lets me unwind recurse while keeping pointer of new node
			if (_comp(val, node->data))//if val is less than search go left
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
			/*if (balance > 1 && _comp(val,node->data))//if out of balance and val is smaller
				return (right_rotate(node));
			else if (balance > 1 && (_comp(node->data, val)))//LR
			{
				node->left = left_rotate(node->left);
				return (right_rotate(node));
			}
			else if (balance < -1 && (_comp(node->right->data, val)))//RR
				return (left_rotate(node));
			else if (balance < -1 && _comp(val, node->right->data))//RL
			{
				node->right = right_rotate(node->right);
				return (left_rotate(node));
			}*/
			if (balance > 1)//then there must be a rotate
			{
				balance = update_height(node->left);
				if (balance >= 0)
					return (right_rotate(node));
				else if (balance < 0)//LR
				{
					node->left = left_rotate(node->left);
					return (right_rotate(node));
				}
			}
			else if (balance < -1)//then there must be a rotate
			{
				balance = update_height(node->right);
				if (balance > 0)
				{
					node->right = right_rotate(node->right);
					return (left_rotate(node));
				}
				else if (balance <= 0)
					return (left_rotate(node));
			}
			return (node);//if no rotate return unchanged pointer
		}
		int	update_height(pointer node)//new nodes start at 1 empty is 0 returns if out of balance
		{//also returns balance
			int lh, rh, balance;
			if (!node)
				return (0);
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
			if (oldroot->left)
				newroot->left = recursive_non_balancing_copy(oldroot->left, newroot);//make sure that parents are correct
			if (oldroot->right)
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
			_alloc.construct(ptr, node<value_type>(val));
			_size++;
			return (ptr);
		}
		void delete_node(pointer ptr)//update all the pointers before calling this
		{
			_alloc.destroy(ptr);
			_alloc.deallocate(ptr, 1);
			_size--;
		}
	};//left if smaller right if equal or bigger... which is what std::less does

} // namespace ft

#endif