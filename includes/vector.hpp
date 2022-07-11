/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:48:59 by rponsonn          #+#    #+#             */
/*   Updated: 2022/07/04 22:37:14 by rponsonn         ###   ########.fr       */
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
		size_type		_size;//current amt of elements
		size_type		_capacity;//how many elements you can add before you need to allocate more
		allocator_type	_alloc;
		public:
		//construct default-fill-range-copy, destruct and operator =
		explicit vector (const allocator_type &alloc = allocator_type()): _ptr(0), _size(0), _capacity(0), _alloc(alloc) {}
		explicit vector (size_type n, const value_type& val = value_type(),const allocator_type& alloc = allocator_type()) : _ptr(0), _size(0), _capacity(0), _alloc(alloc)
		{
			//add function to fill n amount of val in here
			this->assign(n, val);
		}
		template <class Iterator>
		vector(Iterator first, Iterator last, const allocator_type &alloc = allocator_type()): _ptr(0), _size(0), _capacity(0), _alloc(alloc)
		{
			//add function to fill range of values here
			this->assign(first, last);
		}
		vector (const vector& x): _ptr(0), _size(0), _capacity(0), _alloc(x._alloc)
		{
			//add function to copy data from other vector to this one
		}
		~vector()
		{
			//add function to destroy elements properly
			if (_size > 0)
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(&_ptr[i]);
			}
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
		void assign(size_type count, const T &value)//fill
		{
			if (count > _capacity)
				reserve(count);//increase size (reserve)
			for (size_type i = 0; i < _size; i++)//destroy data that might be there
				_alloc.destroy(&_ptr[i]);
			for (size_type i = 0; i < count; i++)//refill count amt of data
				_alloc.construct(&_ptr[i],)
			_size = count;
		}
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last)//need to integrate enable_if, learn SFINAE
		{
			;//do sfinae first
		}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//iterators
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
			return (iterator(_ptr + _size));//you are working on end and getting an iterator to point there
		}
		const_iterator	end(void) const
		{
			return (const_iterator(_ptr + _size));
		}
		reverse_iterator rbegin(void)
		{
			return (reverse_iterator(_ptr + _size));
		}
		const_reverse_iterator rbegin(void)const
		{
			return (const_reverse_iterator(_ptr + _size));
		}
		reverse_iterator rend(void)
		{
			return (reverse_iterator(_ptr));
		}
		const_reverse_iterator rend(void)const
		{
			return (reverse_iterator(_ptr + _size));
		}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Capacity
		//size[x] maxsize[x] resize[x] capacity[] empty[x] reserve[x]
		bool	empty(void)const
		{
			if (_size == 0)
				return (true);
			return (false);
		}
		size_type size(void)const
		{
			return (_size);
		}
		size_type max_size(void)const
		{
			return _alloc.max_size();
		}
		size_type capacity(void)const
		{
			return (_capacity);
		}
		void resize(size_type n, value_type val = value_type())
		{
			if (n > _capacity)
				reserve(n);
			if (n > size)
			{
				for (size_type i = _size; i < n; i++)
					_alloc.construct(&_ptr[i], val);
				_size = n;
			}
			else if ( n < size)
			{
				for (size_type i = n; i < n; i++)
					_alloc.destroy(&_ptr[i]);n == _size)
				return ;
			} 
		}
		void reserve(size_type n)
		{
			size_type new_cap = _capacity;
			value_type *newptr;
			if (_capacity >= n)//if smaller do nothing
				return ;
			else if (n > max_size())
				throw std::length_error("newsize greater than maxsize");
			if (new_cap == 0)
				new_cap = 1;
			while (new_cap < n)
				new_cap *= 2;
			//allocate then move memory if size != 0
			newptr = _alloc.allocate(new_cap);
			for (size_type i = 0; i < _size; i++)
			{
				_alloc.construct(&newptr[i], _ptr[i]);
				_alloc.destroy(&_ptr[i]);
			}
			if (_ptr)
				_alloc.deallocate(_ptr, _capacity);
			_ptr = newptr;
			_capacity = new_cap;
		}
		allocator_type	get_allocator(void) const
		{
			return (_alloc);
		}
		//clear[] insert[] erase[] push_back[] pop_back[] resize[] swap[]
		void	clear(void)
		{
			if (_size > 0)
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(&_ptr[i]);
				_size = 0;
			}
		}
	};
}//namespace ft
#endif
