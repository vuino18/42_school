/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:35:12 by alcarval          #+#    #+#             */
/*   Updated: 2026/04/09 15:35:14 by alcarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->value = NULL;
	tok->quoted = 0;
	tok->next = NULL;
	if (value)
	{
		tok->value = ft_strdup(value);
		if (!tok->value)
		{
			free(tok);
			return (NULL);
		}
	}
	return (tok);
}

void	free_tokens(t_token *tokens)
{
	t_token	*next;

	while (tokens)
	{
		next = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = next;
	}
}

static int	skip_word(char *s)
{
	int		i;
	char	quote;

	i = 0;
	while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '\n'
		&& s[i] != '|' && s[i] != '<' && s[i] != '>')
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
				i++;
			if (s[i] == quote)
				i++;
		}
		else
			i++;
	}
	return (i);
}

static t_token	*next_token(char *s, int *i)
{
	char	*word;
	int		len;
	t_token	*tok;

	while (s[*i] == ' ' || s[*i] == '\t' || s[*i] == '\n')
		(*i)++;
	if (!s[*i])
		return (NULL);
	if (s[*i] == '|' || s[*i] == '<' || s[*i] == '>')
		return (tok_operator(s, i));
	len = skip_word(s + *i);
	word = ft_substr(s, *i, len);
	*i += len;
	tok = new_token(TOK_WORD, word);
	free(word);
	return (tok);
}

t_token	*lexer(char *line)
{
	t_token	*head;
	t_token	*tail;
	t_token	*tok;
	int		i;

	head = NULL;
	tail = NULL;
	i = 0;
	while (line[i])
	{
		tok = next_token(line, &i);
		if (!tok)
			break ;
		if (!head)
			head = tok;
		else
			tail->next = tok;
		tail = tok;
	}
	return (head);
}
