/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:09:54 by elino             #+#    #+#             */
/*   Updated: 2025/07/06 09:00:58 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*start;
	const char	*end;
	char		*res;

	if (!s1 || !set)
		return ((char *)0);
	start = s1;
	end = s1 + ft_strlen(s1);
	while (*start && in_set(*start, set))
		start++;
	while (end > start && in_set(*(end - 1), set))
		end--;
	res = malloc((end - start) + 1);
	if (!res)
		return ((char *)0);
	ft_strlcpy(res, start, (end - start) + 1);
	return (res);
}
