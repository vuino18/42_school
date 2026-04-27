/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:52:43 by elino             #+#    #+#             */
/*   Updated: 2025/07/02 17:21:24 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	if (!s && n > 0)
		return ((void *)0);
	ptr = (unsigned char *)s;
	while (n--)
		*ptr++ = (unsigned char)c;
	return ((void *)s);
}
