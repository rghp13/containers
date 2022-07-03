/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 23:25:45 by rponsonn          #+#    #+#             */
/*   Updated: 2022/07/03 23:41:55 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP
#include "iterator.hpp"
#include "iterator_traits.hpp"
namespace ft
{
	template <class _Iterator>//review this for where a const overload might be necessary (this includes the non-reverse iterator)
	class reverse_iterator
	{
		public:
			typedef typename iterator_traits<_Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<_Iterator>::value_type			value_type;
			typedef typename iterator_traits<_Iterator>::difference_type	difference_type;
			typedef typename iterator_traits<_Iterator>::pointer			pointer;
			typedef typename iterator_traits<_Iterator>::reference			reference;
			typedef _Iterator												iterator_type;
		private:
			iterator_type _base;
		public:
		//constructors
		reverse_iterator(): _base(iterator_type()) {}
		explicit reverse_iterator(iterator_type it): _base(it) {}
		reverse_iterator(const reverse_iterator<_Iterator> &rev_it): _base(rev_it._base) {}//unsure if <_Iterator> is 100% needed
		~reverse_iterator() {}
		//functions
		iterator_type	base() const
		{	return (_base); }
		//operators * + ++ += - -- -= -> []
		reference operator*()const
		{
			_Iterator __tmp = _base;
			return (*(--__tmp));
		}
		reverse_iterator operator+(difference_type n)const
		{
			return (reverse_iterator(_base - n));
		}
		reverse_iterator &operator++()
		{
			--_base;
			return (*this);
		}
		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			--_base;
			return (tmp);
		}
		reverse_iterator &operator+=(difference_type n)
		{
			_base -= n;
			return (*this);
		}
		reverse_iterator operator-(difference_type n)const
		{
			return (reverse_iterator(_base + n));
		}
		reverse_iterator &operator--()
		{
			++_base;
			return (*this);
		}
		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;
			++_base;
			return (tmp);
		}
		reverse_iterator &operator-=(difference_type n)
		{
			_base += n;
			return (*this);
		}
		pointer operator->()const
		{
			return (&(operator*()));
		}
		reference operator[](difference_type n) const
		{
			return *(*this + n);
		}
	};
	//relational operator == != < <= > >=
	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() != rhs.base());
	}
	template <class Iterator>
	bool operator< (const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() > rhs.base());
	}
	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}
	template <class Iterator>
	bool operator> (const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() < rhs.base());
	}
	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}
	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &rev_it)
	{
		return (rev_it + n);
	}
	template <class Iterator>
	reverse_iterator<Iterator> operator-(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &rev_it)
	{
		return (rev_it - n);
	}
};
#endif
