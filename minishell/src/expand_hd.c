/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:34:47 by alcarval          #+#    #+#             */
/*   Updated: 2026/04/09 15:34:49 by alcarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_hd_len(char *s, int *quoted)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	*quoted = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			*quoted = 1;
		else
			len++;
		i++;
	}
	return (len);
}

static char	*strip_hd_delim(char *s, int *quoted)
{
	char	*res;
	int		i;
	int		len;

	len = count_hd_len(s, quoted);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] != '\'' && s[i] != '"')
			res[len++] = s[i];
		i++;
	}
	res[len] = '\0';
	return (res);
}

static void	expand_one_tok(t_token *toks, t_token_type prev, t_shell *sh)
{
	char	*expanded;
	char	*stripped;
	int		quoted;

	if (prev == TOK_HEREDOC)
	{
		stripped = strip_hd_delim(toks->value, &quoted);
		free(toks->value);
		toks->value = stripped;
		toks->quoted = quoted;
	}
	else
	{
		expanded = expand_word(toks->value, sh);
		free(toks->value);
		toks->value = expanded;
	}
}

void	expand_tokens(t_token *toks, t_shell *sh)
{
	t_token_type	prev;

	prev = TOK_WORD;
	while (toks)
	{
		if (toks->type == TOK_WORD)
			expand_one_tok(toks, prev, sh);
		prev = toks->type;
		toks = toks->next;
	}
}
