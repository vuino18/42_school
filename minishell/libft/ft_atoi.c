/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:32:25 by elino             #+#    #+#             */
/*   Updated: 2025/07/05 16:28:45 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handle_overflow(long output, int sign, char c)
{
	if (output > (LONG_MAX - (c - '0')) / 10)
	{
		if (sign == 1)
			return (-1);
		return (0);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	long	output;
	int		sign;
	int		overflow_checker;

	sign = 1;
	output = 0;
	if (!str)
		return (0);
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && (*str >= '0' && *str <= '9'))
	{
		overflow_checker = handle_overflow(output, sign, *str);
		if (overflow_checker != 1)
			return (overflow_checker);
		output = output * 10 + (*str - '0');
		str++;
	}
	return ((int)(output * sign));
}
