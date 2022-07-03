/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:27:34 by rponsonn          #+#    #+#             */
/*   Updated: 2022/07/03 18:52:34 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP
#include "iterator_traits.hpp"
namespace ft
{
	template <class T>
	class	random_access_iterator : public ft::iterator<random_access_iterator_tag, T>
	{

		public:
		typedef	T			value_type;
		typedef	T*			pointer;
		typedef	T&			reference;
		typedef	typename	ft::iterator<random_access_iterator_tag, T>::difference_type	difference_type;
		typedef typename	ft::iterator<random_access_iterator_tag, T>::iterator_category	iterator_category;
		protected:
		pointer _M_current;
		public:
		//construct
		random_access_iterator() : _M_current(0) {}
		random_access_iterator(pointer ptr) : _M_current(ptr) {}
		random_access_iterator(random_access_iterator const &src) : _M_current(src._M_current) {}
		~random_access_iterator() {}
		pointer	base() const	{return(_M_current);}
		//overload * -> and []
		reference	operator*()		{return(*_M_current);}//read stl_iterator.h and stl_vector.h
		pointer		operator->()	{return(_M_current);}
		reference	operator[](difference_type const dif) const {return(*(_M_current[dif]));}
		//overload ++ -- += + -= -
		random_access_iterator	&operator++()
		{
			++_M_current;
			return *this;
		}
		random_access_iterator	operator++(int)
		{	
			return(random_access_iterator(_M_current++));
		}
		random_access_iterator	&operator--()
		{
			--_M_current;
			return *this;
		}
		random_access_iterator	operator--(int)
		{	
			return(random_access_iterator(_M_current--));
		}
		random_access_iterator	operator+=(difference_type dif)
		{
			_M_current += dif;
			return *this;
		}
		random_access_iterator	operator+(difference_type dif)
		{
			return (random_access_iterator(_M_current + dif));
		}
		random_access_iterator	operator-=(difference_type dif)
		{
			_M_current -= dif;
			return *this;
		}
		random_access_iterator operator-(difference_type dif)
		{
			return (random_access_iterator(_M_current - dif));
		}
		random_access_iterator &operator=(random_access_iterator const &src)
		{
			if (&src != this)
				_M_current = src._M_current;
			return *this;
		}
	};
	//comparisons == != > >= < <=
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
	template<class _IteratorL, class _IteratorR>
	bool operator>(_IteratorL const &lhs, _IteratorR const &rhs)
	{
		return (lhs.base() > rhs.base());
	}
	template<class _IteratorL, class _IteratorR>
	bool operator>=(_IteratorL const &lhs, _IteratorR const &rhs)
	{
		return (lhs.base() >= rhs.base());
	}
	template<class _IteratorL, class _IteratorR>
	bool operator<(_IteratorL const &lhs, _IteratorR const &rhs)
	{
		return (lhs.base() < rhs.base());
	}
	template<class _IteratorL, class _IteratorR>
	bool operator<=(_IteratorL const &lhs, _IteratorR const &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

} // namespace ft

#endif
