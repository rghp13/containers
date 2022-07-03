/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:48:59 by rponsonn          #+#    #+#             */
/*   Updated: 2022/07/03 18:52:45 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
#include <memory>//allocator
#include "iterator.hpp"
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
//must implement
//Vector
//Map
namespace ft
{
	template <typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		public:
		typedef T														value_type;
		typedef Alloc													allocator_type;

		typedef typename allocator_type::reference						reference;
		typedef typename allocator_type::const_reference				const_reference;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;

		typedef typename allocator_type::size_type						size_type;
		typedef typename allocator_type::difference_type				difference_type;

		typedef typename ft::random_access_iterator<value_type>			iterator;
		typedef typename ft::random_access_iterator<const value_type>	const_iterator;
		typedef typename ft::reverse_iterator<iterator>					reverse_iterator;//still need to implement
		typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;//still need to implement
		private:
		pointer			_ptr;
		size_type		_size;
		size_type		_capacity;
		allocator_type	_alloc;
		public:
		//construct default-fill-range-copy, destruct and operator =
		explicit vector (const allocator_type &alloc = allocator_type()): _ptr(0), _size(0), _capacity(0), _alloc(alloc) {}
		explicit vector (size_type n, const value_type& val = value_type(),const allocator_type& alloc = allocator_type()) : _ptr(0), _size(0), _capacity(0), _alloc(alloc)
		{
			//add function to fill n amount of val in here
		}
		template <class Iterator>
		vector(Iterator first, Iterator last, const allocator_type &alloc = allocator_type()): _ptr(0), _size(0), _capacity(0), _alloc(alloc)
		{
			//add function to fill range of values here
		}
		vector (const vector& x): _ptr(0), _size(0), _capacity(0), _alloc(x._alloc)
		{
			//add function to copy data from other vector to this one
		}
		~vector()
		{
			//add function to destroy elements properly
			_alloc.deallocate(_ptr, _capacity);
		}
		vector &operator=(vector const &x)
		{
			if (*this == x)
				return (*this);
			//clear current data
			//move data over here
			//update all vars
			return (*this);
		}
		iterator	begin(void)
		{
			return (iterator(_ptr));
		}
		const_iterator	begin(void)const
		{
			return (const_iterator(_ptr));
		}
		iterator	end(void)
		{
			return (iterator(_ptr + _size))//you are working on end and getting an iterator to point there
		}
		const_iterator	end(void) const
		{
			return (const_iterator(_ptr + _size));
		}
		reverse_iterator rbegin(void)
		{
			;
		}
		reverse_iterator rend(void)
		{
			;
		}
	};
}//namespace ft
#endif
