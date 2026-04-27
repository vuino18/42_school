/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:20:48 by elino             #+#    #+#             */
/*   Updated: 2025/07/02 16:35:24 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	j;
	size_t	src_len;
	size_t	i;
	size_t	total_len;
	size_t	dest_len;

	if ((!dest || !src) && size > 0)
		return (0);
	j = 0;
	i = 0;
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (size > dest_len)
		total_len = dest_len + src_len;
	else
		total_len = src_len + size;
	j = dest_len;
	while (src[i] && j + 1 < size)
	{
		dest[j] = src[i];
		j++;
		i++;
	}
	dest[j] = 0;
	return (total_len);
}
