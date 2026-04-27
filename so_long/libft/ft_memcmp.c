/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:51:02 by elino             #+#    #+#             */
/*   Updated: 2025/07/07 11:06:22 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str;
	const unsigned char	*str1;
	size_t				i;

	if ((!s1 && !s2) || n == 0)
		return (0);
	if (!s1 && s2)
		return (-1);
	if (s1 && !s2)
		return (1);
	str = (const unsigned char *)s1;
	str1 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (str[i] != str1[i])
			return (str[i] - str1[i]);
		i++;
	}
	return (0);
}
