/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 13:10:34 by rponsonn          #+#    #+#             */
/*   Updated: 2022/07/24 14:19:07 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
# define TREE_HPP
namespace ft
{
	//node
	enum RB_tree_color { RED = false, BLACK = true};
	template <class T>
	class Rb_node
	{
		typedef T 				value_type;
		typedef Rb_node*		Base_ptr;
		typedef const Rb_node*	Const_Base_ptr;

		RB_tree_color	color;
		Base_ptr		parent;
		Base_ptr		left;
		Base_ptr		right;
		value_type		data;

		Rb_node(value_type &src): data(src) {}
		~Rb_node() {}
	};
} // namespace ft

#endif