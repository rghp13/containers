#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP
#include "iterator_traits.hpp"

namespace ft
{
	template <class T>
	class bidirectional_iterator : public ft::iterator<std::bidirectional_iterator_tag, T>
	{
		public:
		typedef T								node_type;
		typedef node_type*						node_pointer;
		typedef node_type&						node_ref;
		typedef typename node_type::value_type	data_type;
		typedef data_type						*data_pointer;
		typedef data_type const					*const_data_pointer;
		typedef data_type						&data_ref;
		typedef data_type const					&const_data_ref;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::difference_type	difference_type;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
		private:
		node_pointer	ptr;
		//construct
		bidirectional_iterator(): ptr(0) {}
		bidirectional_iterator(node_pointer other): ptr(other) {}
		bidirectional_iterator(bidirectional_iterator const &src): ptr(src.ptr) {}
		~bidirectional_iterator() {}
		bidirectional_iterator &operator=(bidirectional_iterator const &x)
		{
			if (this != &x)
				ptr = x.ptr;
			return (*this);
		}
		node_pointer			base(void) const	{return (ptr);}
		node_reference			operator*()			{return(*ptr);}
		node_pointer			operator->()		{return(ptr);}
		bidirectional_iterator	&operator++()
		{
			if (ptr->right)
			{
				ptr = ptr->right;
				while (ptr->left)
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
			if (ptr->left)
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
			}
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