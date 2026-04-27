/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 10:53:27 by elino             #+#    #+#             */
/*   Updated: 2026/03/25 10:53:29 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_sign(char *str, int *i, int *neg)
{
	*i = 0;
	*neg = 0;
	if (str[*i] == '+' || str[*i] == '-')
	{
		*neg = (str[*i] == '-');
		(*i)++;
	}
}

int	is_overflow(char *str)
{
	unsigned long long	limit;
	unsigned long long	n;
	int					i;
	int					neg;

	parse_sign(str, &i, &neg);
	limit = 9223372036854775807LL;
	n = 0;
	while (str[i])
	{
		if (n > (limit - (str[i] - '0')) / 10)
			return (1);
		n = n * 10 + (str[i] - '0');
		i++;
	}
	if (neg && n > 9223372036854775808ULL)
		return (1);
	if (!neg && n > limit)
		return (1);
	return (0);
}

int	get_exit_code(char *str)
{
	long long	n;
	int			i;
	int			neg;

	parse_sign(str, &i, &neg);
	n = 0;
	while (str[i])
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	if (neg)
		n = -n;
	return ((int)(n & 255));
}

int	is_numeric(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
