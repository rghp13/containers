/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 18:08:28 by rponsonn          #+#    #+#             */
/*   Updated: 2022/07/21 12:39:34 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP
namespace ft
{
	template <bool cond, class T = void>
	struct enable_if {};
	template <class T>
	struct enable_if<true, T> {typedef T type;};
} //namespace ft

#endif