/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_safe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:59:57 by elino             #+#    #+#             */
/*   Updated: 2025/10/31 11:22:10 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	handle_overflow(long output, char c)
{
	if (output > (LONG_MAX - (c - '0')) / 10)
		return (0);
	return (1);
}

static int	skip_spaces_and_sign(const char **str)
{
	int	sign;

	sign = 1;
	while ((**str >= 9 && **str <= 13) || **str == ' ')
		(*str)++;
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

long	ft_atoi_safe(const char *str, int *is_valid)
{
	long	output;
	int		sign;

	*is_valid = 1;
	if (!str || !*str)
		return (*is_valid = 0, 0);
	sign = skip_spaces_and_sign(&str);
	if (!(*str >= '0' && *str <= '9'))
		return (*is_valid = 0, 0);
	output = 0;
	while (*str && *str >= '0' && *str <= '9')
	{
		if (!handle_overflow(output, *str))
			return (*is_valid = 0, 0);
		output = output * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0')
		return (*is_valid = 0, 0);
	return (output * sign);
}
