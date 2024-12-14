/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:48:53 by sde-carv          #+#    #+#             */
/*   Updated: 2024/12/14 11:04:18 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_handle_overflow(int sign)
{
	if (sign == -1)
		return (LLONG_MIN);
	return (LLONG_MAX);
}

int	ft_get_base(const char **str, int base)
{
	if (base == 0)
	{
		if (**str == '0' && ((*str)[1] == 'x' || (*str)[1] == 'X'))
		{
			*str += 2;
			return (16);
		}
		if (**str == '0')
			return (8);
		return (10);
	}
	if (base == 16 && **str == '0' && ((*str)[1] == 'x' || (*str)[1] == 'X'))
		*str += 2;
	return (base);
}

long long	ft_strtoll_parse(const char **str, int *sign, int base)
{
	int			digit;
	long long	result;

	result = 0;
	while (**str)
	{
		digit = ft_get_digit(**str);
		if (digit < 0 || digit >= base)
			break ;
		if (result > (LLONG_MAX - digit) / base)
			return (ft_handle_overflow(*sign));
		result = result * base + digit;
		(*str)++;
	}
	return (result);
}

long long	ft_strtoll(const char *str, char **endptr, int base)
{
	int			sign;
	long long	result;

	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	base = ft_get_base(&str, base);
	result = ft_strtoll_parse(&str, &sign, base);
	if (endptr != NULL)
		*endptr = (char *)str;
	return (result * sign);
}
