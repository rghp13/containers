/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:48:59 by rponsonn          #+#    #+#             */
/*   Updated: 2022/11/17 17:39:50 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
#include <memory>//allocator
#include <exception>
#include <iterator>
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include "lexicographical_compare.hpp"
#include "equal.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"
//must implement
//Vector
//Map
namespace ft
{
	template <typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		public:
		typedef T														value_type;//
		typedef Alloc													allocator_type;//

		typedef typename allocator_type::reference						reference;
		typedef typename allocator_type::const_reference				const_reference;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;

		typedef typename allocator_type::size_type						size_type;
		typedef typename allocator_type::difference_type				difference_type;

		template <class Tt, bool isconst = false>
		class	random_access_iterator : public ft::iterator<std::random_access_iterator_tag, Tt>
		{

			public:
			typedef	Tt			value_type;
			typedef	Tt*			pointer;
			typedef	Tt&			reference;
			typedef	typename	ft::iterator<std::random_access_iterator_tag, Tt>::difference_type	difference_type;
			typedef typename	ft::iterator<std::random_access_iterator_tag, Tt>::iterator_category	iterator_category;
			protected:
			pointer _M_current;
			public:
			//construct
			random_access_iterator() : _M_current(0) {}
			random_access_iterator(pointer ptr) : _M_current(ptr) {}
			random_access_iterator(random_access_iterator const &src) : _M_current(src._M_current) {}
			~random_access_iterator() {}
			//overload * -> and []
			//pointer		base() const	{return(_M_current);}//base is only for reverse iterators apparently
			reference	operator*()		{return(*_M_current);}//read stl_iterator.h and stl_vector.h
			pointer		operator->()	{return(_M_current);}
			reference	operator[](difference_type const dif) const {return(_M_current[dif]);}//random
			random_access_iterator &operator=(random_access_iterator const &src)
			{
				if (&src != this)
					_M_current = src._M_current;
				return (*this);
			}
			//
			/*template <bool B>
			random_access_iterator(const random_access_iterator<Tt, B> &src, typename ft::enable_if<!B>::type* = 0)
			{
				_M_current = src._M_current;
			}*/
			operator random_access_iterator<const Tt, true>()const//conversion from non-const to const
			{
				return (random_access_iterator<const Tt, true>(_M_current));
			}
			//overload ++ -- += + -= -
			random_access_iterator	&operator++()
			{
				++_M_current;
				return (*this);
			}
			random_access_iterator	operator++(int)
			{	
				return(random_access_iterator(_M_current++));
			}
			random_access_iterator	&operator--()
			{
				--_M_current;
				return (*this);
			}
			random_access_iterator	operator--(int)
			{	
				return(random_access_iterator(_M_current--));
			}
			random_access_iterator	operator+=(difference_type dif)//random
			{
				_M_current += dif;
				return (*this);
			}
			random_access_iterator	operator+(difference_type dif)const//random
			{
				return (random_access_iterator(_M_current + dif));
			}
			random_access_iterator	operator-=(difference_type dif)//random
			{
				_M_current -= dif;
				return (*this);
			}
			random_access_iterator operator-(difference_type dif)const//random Add another iterator
			{
				return (random_access_iterator(_M_current - dif));
			}
			difference_type operator-(random_access_iterator<Tt, false> const &src)const
			{
				return (_M_current - src._M_current);
			}
			difference_type operator-(random_access_iterator<Tt, true> const &src)const
			{
				return (_M_current - src._M_current);
			}
			//comparisons == != > >= < <=
			bool operator==(random_access_iterator<Tt, false> src)const
			{
				return (_M_current == &(*src));
			}
			bool operator!=(random_access_iterator<Tt, false> src)const
			{
				return (_M_current != &(*src));
			}
			bool operator<(random_access_iterator<Tt, false> src)const
			{
				return (_M_current < &(*src));
			}
			bool operator<=(random_access_iterator<Tt, false> src)const
			{
				return (_M_current <= &(*src));
			}
			bool operator>(random_access_iterator<Tt, false> src)const
			{
				return (_M_current > &(*src));
			}
			bool operator>=(random_access_iterator<Tt, false> src)const
			{
				return (_M_current >= &(*src));
			}
			bool operator==(random_access_iterator<const Tt, true> src)const
			{
				return (_M_current == &(*src));
			}
			bool operator!=(random_access_iterator<const Tt, true> src)const
			{
				return (_M_current != &(*src));
			}
			bool operator<(random_access_iterator<const Tt, true> src)const
			{
				return (_M_current < &(*src));
			}
			bool operator<=(random_access_iterator<const Tt, true> src)const
			{
				return (_M_current <= &(*src));
			}
			bool operator>(random_access_iterator<const Tt, true> src)const
			{
				return (_M_current > &(*src));
			}
			bool operator>=(random_access_iterator<const Tt, true> src)const
			{
				return (_M_current >= &(*src));
			}
		};
		template<typename ItT, bool isconst>
		friend random_access_iterator<ItT, isconst> operator+(typename random_access_iterator<ItT, isconst>::difference_type dif, random_access_iterator<ItT, isconst> const &src)
		{
			return (random_access_iterator<ItT, isconst>(src + dif));
		}//added to handle int + iterator cases had to add friend for type access
		typedef random_access_iterator<value_type>				iterator;
		typedef random_access_iterator<const value_type, true>	const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
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
			assign(n, val);
		}
		template <class Iterator>
		vector(Iterator first, Iterator last, const allocator_type &alloc = allocator_type()): _ptr(0), _size(0), _capacity(0), _alloc(alloc)
		{
			//add function to fill range of values here
			assign(first, last);
		}
		vector (const vector& x): _ptr(0), _size(0), _capacity(0), _alloc(x._alloc)
		{
			*this = x;
		}
		~vector()
		{
			//add function to destroy elements properly
			clear();
			_alloc.deallocate(_ptr, _capacity);
		}
		vector &operator=(vector const &x)
		{
			if (*this == x)
				return (*this);
			//clear current data
			clear();
			_alloc.deallocate(_ptr, _capacity);//doing this so that capacity is the same as the source vector
			_ptr = 0;
			_alloc = x._alloc;
			_capacity = 0;
			reserve(x._capacity);
			//move data over here
			assign(x.begin(), x.end());
			//update all vars
			return (*this);
		}
		void assign(size_type count, const T &value)//fill
		{
			clear();
			if (count > _capacity)
				reserve(count);//increase size (reserve)
			for (size_type i = 0; i < count; i++)//refill count amt of data
				_alloc.construct(&_ptr[i], value);
			_size = count;
		}
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
		{
			clear();
			size_type n = std::distance(first, last);//including the element pointed by first but not the element pointed by last.
			if (n > _capacity)
				reserve(n);
			for (size_type i = 0; first != last; first++)
				_alloc.construct(&_ptr[i++], *first);
			_size = n;
		}
		allocator_type	get_allocator(void) const
		{
			return (_alloc);
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
			return (const_reverse_iterator(_ptr));
		}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Capacity
		//size[x] maxsize[x] resize[x] capacity[x] empty[x] reserve[x] 
		size_type size(void)const
		{
			return (_size);
		}
		size_type max_size(void)const
		{
			return (_alloc.max_size());
		}
		void resize(size_type n, value_type val = value_type())
		{
			if (n > _capacity)
				reserve(n);
			if (n > _size)
			{
				for (size_type i = _size; i < n; i++)
					_alloc.construct(&_ptr[i], val);
				_size = n;
			}
			else if ( n < _size)
			{
				for (size_type i = n; i < _size; i++)
					_alloc.destroy(&_ptr[i]);
				_size = n;
				return ;
			} 
		}
		size_type capacity(void)const
		{
			return (_capacity);
		}
		bool	empty(void)const
		{
			if (_size <= 0)
				return (true);
			return (false);
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
		//clear[x] insert[x] erase[x] push_back[x] pop_back[x] swap[x]
		void	clear(void)
		{
			if (_size > 0)
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(&_ptr[i]);
				_size = 0;
			}
		}
		//insert before element at position pos, increase size by number of element added
		//ONLY reallocate if capacity is increased
		iterator insert(iterator pos, const value_type &val)//single element
		{
			size_type i = &*pos - &*begin();//should return distance from start and not break with reallocation
			if (_size == _capacity)
				reserve(_size + 1);
			shiftr(i, 1);
			_alloc.construct(&_ptr[i], val);
			_size += 1;
			return (iterator(_ptr + i));
		}
		void insert(iterator pos, size_type n, const value_type &val)//fill
		{
			size_type start = &*pos - &*begin();
			if (_size + n > _capacity)
				reserve(_size + n);
			shiftr(start, n);
			for (size_type i = start; i < start + n; i++)
				_alloc.construct(&_ptr[i], val);
			_size += n;
		}
		template <class InputIterator>
		void insert(iterator pos, InputIterator first, InputIterator last, 
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)//range
		{
			size_type start = &*pos - &*begin();
			size_type n = std::distance(first, last);

			if (_size + n > _capacity)
				reserve(_size + n);
			shiftr(start, n);
			for (size_type i = start; i < start + n; i++, first++)
				_alloc.construct(&_ptr[i], *first);
			_size += n;
		}
		iterator erase(iterator pos)//removes a single item then shift left
		{
			size_type i = &*pos - &*begin();//no need to protect from erasing an empty vector
			_alloc.destroy(&_ptr[i++]);
			shiftl(i, 1);
			_size -= 1;
			return (pos);
		}

		iterator erase(iterator first, iterator last)
		{
			size_type f = &*first - &*begin();
			size_type l = &*last - &*begin();
			size_type n = l - f;
			for (size_type i = f; i < l; i++)
				_alloc.destroy(&_ptr[i]);
			if (last != end())//dont shift if last is end
				shiftl(l, n);//
			_size -= n;
			return (first);
		}
		void push_back(const value_type &val)
		{
			if (_size + 1 > _capacity)
				reserve(_size + 1);
			_alloc.construct(&_ptr[_size++], val);
		}
		void pop_back(void)
		{
				_alloc.destroy(&_ptr[--_size]);
		}
		void swap(vector &x)
		{
			if (this == &x)
				return;
			std::swap(_ptr, x._ptr);
			std::swap(_size, x._size);
			std::swap(_capacity, x._capacity);
			std::swap(_alloc, x._alloc);
		}
		//element access = operator[x], at[x], front[x], back[x]
		reference operator[](size_type n)
		{
			return (_ptr[n]);
		}
		const_reference operator[](size_type n)const
		{
			return (_ptr[n]);
		}
		reference at(size_type n)
		{
			if (n >= _size)
				throw std::out_of_range("no valid element at this position");
			return (_ptr[n]);
		}
		const_reference at (size_type n)const
		{
			if (n >= _size)
				throw std::out_of_range("no valid element at this position");
			return (_ptr[n]);
		}
		reference front(void)
		{
			return (_ptr[0]);
		}
		const_reference front(void)const
		{
			return (_ptr[0]);
		}
		reference back(void)
		{
			return (_ptr[_size - 1]);
		}
		const_reference back(void) const
		{
			return (_ptr[_size - 1]);
		}
		pointer data(void)
		{
			return (_ptr);
		}
		const_pointer data(void)const
		{
			return (_ptr);
		}
		private:
		void shiftr(size_type start, size_type n)//make sure that there is space to shift before calling function
		{
			if (_size == 0 || n == 0)
				return ;
			for (size_type i = _size - 1; i >= start; i--)//starts from end of array
			{
				_alloc.construct((_ptr + (i + n)), _ptr[i]);
				_alloc.destroy(&_ptr[i]);
				if (i == start)
					break;
			}
		}
		//start is where the first piece of valid data to shift is
		void shiftl(size_type start, size_type n)//make sure that you've already destroyed what you're shifting into
		{
			if (_size == 0 || n == 0)
				return;
			for (size_type i = start; i < _size; i++)
			{
				_alloc.construct((_ptr + (i - n)), _ptr[i]);
				_alloc.destroy(&_ptr[i]);
			}
		}
	};
	//non relational operator, ==[x], !=[x], <[x], <=[x], >[x], >=[x], swap[x]
	template <class T, class Alloc>//you should only build == and < then use those for all others
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() == rhs.size())//learn about lexicographical compare to complete this
			return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		return (false);
	}
	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}
	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(rhs < lhs));
	}
	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (rhs < lhs);
	}
	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}
	template <class T, class Alloc>
	void swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
	{
		x.swap(y);
	}
}//namespace ft
#endif