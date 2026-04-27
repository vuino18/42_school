/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:12:02 by elino             #+#    #+#             */
/*   Updated: 2025/07/02 17:24:47 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	if (!str)
		return ((char *)0);
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)(str));
		str++;
	}
	if ((char)c == '\0')
		return ((char *)str);
	return ((void *)0);
}
