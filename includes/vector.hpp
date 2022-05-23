/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:48:59 by rponsonn          #+#    #+#             */
/*   Updated: 2022/05/23 23:48:33 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
#include <memory>//allocator
//must implement
//Vector
//Map
//Stack
namespace ft 
{
	template <typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		public:
		//create iterator somehow
		template<typename iterT, bool isconst = false>
		class Viterator
		{
			private:
				iterT	*_it;
			public:
				typedef iterT							value_type;
				typedef ptrdiff_t						difference_type;
				typedef iterT*							pointer;
				typedef iterT&							reference;
				typedef std::random_access_iterator_tag	iterator_category;//double check if std can be used
		};
		typedef T								value_type;
		typedef Alloc							allocator_type;
		typedef typename allocator_type::reference		reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;//might need to add typename
		typedef typename allocator_type::const_pointer	const_pointer;
		typedef Viterator<value_type>			iterator;
	};
}//namespace ft
#endif