/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:35:12 by alcarval          #+#    #+#             */
/*   Updated: 2026/04/09 15:35:14 by alcarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tok_operator(char *s, int *i)
{
	if (s[*i] == '|' && s[*i + 1] == '|')
		return (*i += 2, new_token(TOK_OR, "||"));
	if (s[*i] == '|')
		return ((*i)++, new_token(TOK_PIPE, "|"));
	if (s[*i] == '<' && s[*i + 1] == '<')
		return (*i += 2, new_token(TOK_HEREDOC, NULL));
	if (s[*i] == '>' && s[*i + 1] == '>')
		return (*i += 2, new_token(TOK_REDIR_APPEND, NULL));
	if (s[*i] == '<')
		return ((*i)++, new_token(TOK_REDIR_IN, NULL));
	if (s[*i] == '>')
		return ((*i)++, new_token(TOK_REDIR_OUT, NULL));
	return (NULL);
}
