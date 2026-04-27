/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:42:44 by elino             #+#    #+#             */
/*   Updated: 2025/08/05 12:08:07 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

size_t	ft_strlen(const char *s)
{
	const char	*start;

	if (!s)
		return (0);
	start = s;
	while (*s)
		s++;
	return ((size_t)(s - start));
}

char	*ft_strdup(const char *src)
{
	size_t		i;
	char		*dest;

	if (!src)
		return ((char *)0);
	i = 0;
	dest = malloc((ft_strlen(src) + 1));
	if (!dest)
		return ((char *)0);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*dest;
	size_t		i;
	size_t		j;

	if (!s1 || !s2)
		return ((char *)0);
	i = 0;
	while (s1[i])
		i++;
	j = 0;
	while (s2[j])
		j++;
	dest = malloc(i + j + 1);
	if (!dest)
		return ((char *)0);
	while (*s1)
		*dest++ = *s1++;
	while (*s2)
		*dest++ = *s2++;
	*dest = '\0';
	return (dest - i - j);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*substr;

	if (!s)
		return ((char *)0);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	substr = (char *) malloc(sizeof(char) * (len + 1));
	if (!substr)
		return ((char *)0);
	i = 0;
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
