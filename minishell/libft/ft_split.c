/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:11:24 by elino             #+#    #+#             */
/*   Updated: 2025/07/04 11:50:43 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	counter(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	*ft_str(char const *s, char c)
{
	int		i;
	char	*ptr;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	ptr = malloc(sizeof(char) * (i + 1));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s, i + 1);
	return (ptr);
}

static void	free_memory(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static int	fill_array(char **ptr, char const *s, char c, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		while (*s == c)
			s++;
		ptr[i] = ft_str(s, c);
		if (!ptr[i])
		{
			free_memory(ptr);
			return (0);
		}
		s += ft_strlen(ptr[i]);
		i++;
	}
	ptr[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		strs_len;

	if (!s)
		return (NULL);
	strs_len = counter(s, c);
	ptr = ft_calloc(sizeof(char *), (strs_len + 1));
	if (!ptr)
		return (NULL);
	if (!fill_array(ptr, s, c, strs_len))
		return (NULL);
	return (ptr);
}
