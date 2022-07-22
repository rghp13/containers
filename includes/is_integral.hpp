/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 18:31:12 by rponsonn          #+#    #+#             */
/*   Updated: 2022/07/22 14:13:12 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP
/*
bool
char
char16_t
char32_t
wchar_t
signed char
short int
int
long int
long long int
unsigned char
unsigned short int
unsigned int
unsigned long int
unsigned long long int
*/
namespace ft
{
	template <class T>
	struct is_integral
	{
		const static bool value = false;
	};
	template <>
	struct is_integral<bool>
	{
		const static bool value = true;
	};
	template <>
	struct is_integral<char>
	{
		const static bool value = true;
	};
	template <>
	struct is_integral<char16_t>//probably removing due to being C++11
	{
		const static bool value = true;
	};
	template <>
	struct is_integral<char32_t>//probably removing due to being C++11
	{
		const static bool value = true;
	};
	template <>
	struct is_integral<wchar_t>
	{
		const static bool value = true;
	};
	template <>
	struct is_integral<signed char>
	{
		const static bool value = true;
	};
	template <>
	struct is_integral<short int>
	{
		const static bool value = true;
	};
	template <>
	struct is_integral<int>
	{
		const static bool value = true;
	};
	template <>
	struct is_integral<long int>
	{
		const static bool value = true;
	};
	template <>
	struct is_integral<long long int>
	{
		const static bool value = true;
	};
	template <>
	struct is_integral<unsigned char>
	{
		const static bool value = true;
	};
	template <>
	struct is_integral<unsigned short int>
	{
		const static bool value = true;
	};
	template <>
	struct is_integral<unsigned int>
	{
		const static bool value = true;
	};
	template <>
	struct is_integral<unsigned long int>
	{
		const static bool value = true;
	};
	template <>
	struct is_integral<unsigned long long int>
	{
		const static bool value = true;
	};
} // namespace ft

#endif