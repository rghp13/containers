/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 23:25:45 by rponsonn          #+#    #+#             */
/*   Updated: 2022/11/17 03:44:07 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP
#include "iterator_traits.hpp"
namespace ft
{
	template <class _Iterator>//review this for where a const overload might be necessary (this includes the non-reverse iterator)
	class reverse_iterator
	{
		public:
			typedef typename ft::iterator_traits<_Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<_Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<_Iterator>::difference_type	difference_type;
			typedef typename ft::iterator_traits<_Iterator>::pointer			pointer;
			typedef typename ft::iterator_traits<_Iterator>::reference			reference;
			typedef _Iterator												iterator_type;
		protected:
			iterator_type current;
		public:
		//constructors
		reverse_iterator(): current(iterator_type()) {}
		explicit reverse_iterator(iterator_type it): current(it) {}//consider it = iterator_type()
		template <class U>
		reverse_iterator(const reverse_iterator<U> &other): current(other.base()) {}
		~reverse_iterator() {}
		template <class U>
		reverse_iterator &operator=(const reverse_iterator<U> &other)
		{
			if (this != &other)
				current = other.current;
			return (*this);
		}
		//functions
		iterator_type	base() const
		{	return (current); }
		//operators * + ++ += - -- -= -> []
		reference operator*()const
		{
			_Iterator __tmp = current;
			return (*(--__tmp));
		}
		pointer operator->()const
		{
			return (&(operator*()));
		}
		reference operator[](difference_type n) const
		{
			return *(*this + n);
		}
		reverse_iterator operator+(difference_type n)const
		{
			return (reverse_iterator(current - n));
		}
		reverse_iterator &operator++()
		{
			--current;
			return (*this);
		}
		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			--current;
			return (tmp);
		}
		reverse_iterator &operator+=(difference_type n)
		{
			current -= n;
			return (*this);
		}
		reverse_iterator operator-(difference_type n)const
		{
			return (reverse_iterator(current + n));
		}
		reverse_iterator &operator--()
		{
			++current;
			return (*this);
		}
		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;
			++current;
			return (tmp);
		}
		reverse_iterator &operator-=(difference_type n)
		{
			current += n;
			return (*this);
		}
	};
	//relational operator == != < <= > >=

	template <class Iterator1, class Iterator2>
	bool operator== (const ft::reverse_iterator<Iterator1> &lhs, const ft::reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator!= (const ft::reverse_iterator<Iterator1> &lhs, const ft::reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator< (const ft::reverse_iterator<Iterator1> &lhs, const ft::reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator<= (const ft::reverse_iterator<Iterator1> &lhs, const ft::reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator> (const ft::reverse_iterator<Iterator1> &lhs, const ft::reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator>= (const ft::reverse_iterator<Iterator1> &lhs, const ft::reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator>
	ft::reverse_iterator<Iterator> operator+(typename ft::reverse_iterator<Iterator>::difference_type n, const ft::reverse_iterator<Iterator> &rev_it)
	{
		return (rev_it + n);
	}
	//example == ft::reverse_iterator<ft::vector<int>::iterator> it2 { 2 + it1}//it1 is some other iterator
	template <class Iterator>
	ft::reverse_iterator<Iterator> operator-(typename ft::reverse_iterator<Iterator>::difference_type n, const ft::reverse_iterator<Iterator> &rev_it)
	{
		return (rev_it.base() - n);
	}
	//added to pass testers but is technically c++11
	template <class iter1, class iter2>
	typename ft::reverse_iterator<iter1>::difference_type operator-(const ft::reverse_iterator<iter1> &lhs, const ft::reverse_iterator<iter2> &rhs)
	{
		return (rhs.base() - lhs.base());
	}
}//ft
#endif
