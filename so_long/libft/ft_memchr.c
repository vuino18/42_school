/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:06:57 by elino             #+#    #+#             */
/*   Updated: 2025/06/29 10:13:49 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int value, size_t n)
{
	const unsigned char	*ptr;

	if (!s)
		return ((void *)0);
	ptr = (const unsigned char *)s;
	while (n--)
	{
		if (*ptr == (unsigned char)value)
			return ((void *)(ptr));
		ptr++;
	}
	return ((void *)0);
}
