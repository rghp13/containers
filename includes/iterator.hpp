/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:27:34 by rponsonn          #+#    #+#             */
/*   Updated: 2022/05/31 22:29:45 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP
#include <iterator>
#include <vector>
namespace ft
{
	//set up tags
	struct	input_iterator_tag {};
	struct	output_iterator_tag {};
	struct	forward_iterator_tag : public input_iterator_tag {};
	struct	bidirectional_iterator_tag : public forward_iterator_tag {};
	struct	random_access_iterator_tag : public bidirectional_iterator_tag {};

	template<typename Category, class T, class Distance = ptrdiff_t,
			 typename _Pointer = T*, class _Refererence = T&>
	struct iterator
	{
		typedef	Category		iterator_category;
		typedef	T				value_type;
		typedef	Distance		difference_type;
		typedef	_Pointer		pointer;
		typedef	_Refererence	reference;
	};
	template<class Iterator>
	struct iterator_traits
	{
		typedef typename		iterator::iterator_category	iterator_category;
		typedef typename		iterator::value_type		value_type;
		typedef typename		iterator::difference_type	difference_type;
		typedef typename		iterator::pointer			pointer;
		typedef	typename		iterator::reference			reference;
	};
	template <class _Tp>
	struct	iterator_traits<_Tp*>
	{
		typedef random_access_iterator_tag	iterator_category;
		typedef	_Tp							value_type;
		typedef	ptrdiff_t					difference_type;
		typedef	_Tp*						pointer;
		typedef	_Tp&						reference;
	};
	template <class _Tp>
	struct	iterator_traits<const _Tp*>
	{
		typedef random_access_iterator_tag	iterator_category;
		typedef	_Tp							value_type;
		typedef	ptrdiff_t					difference_type;
		typedef	const _Tp*					pointer;
		typedef	const _Tp&					reference;
	};
	template <class T>
	class	random_access_iterator : public ft::iterator<random_access_iterator_tag, T>//public or private?
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
		reference	operator[](difference_type dif const) const {return(*(_M_current[dif]));}
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
	};
} // namespace ft

#endif