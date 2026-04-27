/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 10:04:58 by elino             #+#    #+#             */
/*   Updated: 2025/11/22 15:32:25 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	count_words(char *s)
{
	int	words;
	int	in;
	int	q;

	words = 0;
	in = 0;
	q = 0;
	while (*s)
	{
		if ((*s == '\'' || *s == '"') && q == 0)
			q = *s;
		else if (*s == q)
			q = 0;
		else if (*s == ' ' && q == 0)
			in = 0;
		else if (in == 0)
		{
			in = 1;
			words++;
		}
		s++;
	}
	return (words);
}

static int	word_len(char **s, char **start)
{
	int	len;
	int	q;

	q = 0;
	len = 0;
	while (**s == ' ')
		(*s)++;
	*start = *s;
	while ((*start)[len] && (q || (*start)[len] != ' '))
	{
		if (((*start)[len] == '\'' || (*start)[len] == '"') && q == 0)
			q = (*start)[len];
		else if ((*start)[len] == q)
			q = 0;
		len++;
	}
	return (len);
}

static char	*extract_word(char **s)
{
	char	*start;
	char	*w;
	int		len;
	int		q;
	int		i;

	i = 0;
	q = 0;
	len = word_len(s, &start);
	w = malloc(len + 1);
	if (!w)
		return (NULL);
	while (**s && (q || **s != ' '))
	{
		if ((**s == '\'' || **s == '"') && q == 0)
			q = **s;
		else if (**s == q)
			q = 0;
		else
			w[i++] = **s;
		(*s)++;
	}
	w[i] = '\0';
	return (w);
}

char	**parse_command(char *cmd)
{
	int		wc;
	int		i;
	char	**arr;
	char	*ptr;

	wc = count_words(cmd);
	arr = malloc(sizeof(char *) * (wc + 1));
	if (!arr)
		return (NULL);
	ptr = cmd;
	i = 0;
	while (i < wc)
	{
		arr[i] = extract_word(&ptr);
		if (!arr[i])
		{
			free_array(arr);
			return (NULL);
		}
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
