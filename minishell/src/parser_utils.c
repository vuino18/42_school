/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:35:27 by alcarval          #+#    #+#             */
/*   Updated: 2026/04/09 15:35:29 by alcarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*tok_name(t_token *tok)
{
	if (tok->type == TOK_PIPE)
		return ("|");
	if (tok->type == TOK_OR)
		return ("||");
	if (tok->type == TOK_REDIR_IN)
		return ("<");
	if (tok->type == TOK_REDIR_OUT)
		return (">");
	if (tok->type == TOK_REDIR_APPEND)
		return (">>");
	if (tok->type == TOK_HEREDOC)
		return ("<<");
	if (tok->value)
		return (tok->value);
	return ("newline");
}

int	syntax_error(const char *token_str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd((char *)token_str, 2);
	ft_putstr_fd("'\n", 2);
	return (1);
}

int	check_pipe_tok(t_token *cur, int prev_is_pipe)
{
	if (prev_is_pipe)
		return (syntax_error("|"));
	if (!cur->next)
		return (syntax_error("newline"));
	return (0);
}

void	unlink_tok(t_token **toks, t_token **prev, t_token **cur)
{
	t_token	*tmp;

	tmp = *cur;
	if (*prev)
		(*prev)->next = (*cur)->next;
	else
		*toks = (*cur)->next;
	*cur = (*cur)->next;
	free(tmp->value);
	free(tmp);
}
