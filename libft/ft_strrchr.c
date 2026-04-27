/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:20:28 by elino             #+#    #+#             */
/*   Updated: 2025/06/26 16:44:46 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	const char	*ptr;

	if (!str)
		return ((char *)0);
	ptr = (void *)0;
	while (*str)
	{
		if (*str == (char)c)
			ptr = str;
		str++;
	}
	if ((char)c == '\0')
		return ((char *)str);
	return ((char *)ptr);
}
