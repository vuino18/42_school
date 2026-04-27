/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:59:15 by elino             #+#    #+#             */
/*   Updated: 2025/07/02 17:33:50 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *substr, size_t size)
{
	size_t	i;
	size_t	j;

	if (!str || !substr)
		return ((char *)0);
	if (*substr == '\0')
		return ((char *)(str));
	i = 0;
	while (str[i] && i < size)
	{
		j = 0;
		while (substr[j] && str[i + j] == substr[j] && i + j < size)
		{
			j++;
		}
		if (substr[j] == '\0')
			return ((char *)(str + i));
		i++;
	}
	return ((char *)0);
}
