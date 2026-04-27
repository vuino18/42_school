/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:52:02 by elino             #+#    #+#             */
/*   Updated: 2025/06/26 16:47:56 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	copy_str(char *dest, const char *src, int *i)
{
	int	j;

	j = 0;
	while (src[j])
	{
		dest[*i] = src[j];
		(*i)++;
		j++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*dest;
	int			len1;
	int			len2;
	int			i;

	if (!s1 || !s2)
		return ((char *)0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	dest = malloc(len1 + len2 + 1);
	if (!dest)
		return ((char *)0);
	i = 0;
	copy_str(dest, s1, &i);
	copy_str(dest, s2, &i);
	dest[i] = '\0';
	return (dest);
}
