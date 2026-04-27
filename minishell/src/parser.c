/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:35:27 by alcarval          #+#    #+#             */
/*   Updated: 2026/04/09 15:35:29 by alcarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_unclosed_quotes(char *s)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '"') && quote == 0)
			quote = s[i];
		else if (s[i] == quote)
			quote = 0;
		i++;
	}
	return (quote != 0);
}

int	check_syntax(t_token *toks)
{
	t_token	*cur;
	int		prev_is_pipe;

	cur = toks;
	prev_is_pipe = 0;
	if (toks && (toks->type == TOK_PIPE || toks->type == TOK_OR))
		return (syntax_error(tok_name(toks)));
	while (cur)
	{
		if (cur->type == TOK_OR)
			return (syntax_error("||"));
		if (cur->type == TOK_PIPE)
		{
			if (check_pipe_tok(cur, prev_is_pipe))
				return (1);
			prev_is_pipe = 1;
		}
		else
			prev_is_pipe = 0;
		cur = cur->next;
	}
	return (0);
}

void	remove_empty_tokens(t_token **toks)
{
	t_token	*cur;
	t_token	*prev;

	cur = *toks;
	prev = NULL;
	while (cur)
	{
		if (cur->type == TOK_WORD && cur->value && cur->value[0] == '\0')
			unlink_tok(toks, &prev, &cur);
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}

static t_cmd	*parse_tokens(t_token *toks, t_shell *shell)
{
	t_cmd	*cmds;

	expand_tokens(toks, shell);
	remove_empty_tokens(&toks);
	if (check_syntax(toks))
	{
		free_tokens(toks);
		shell->last_status = 2;
		return (NULL);
	}
	cmds = build_pipeline(toks);
	free_tokens(toks);
	return (cmds);
}

t_cmd	*parse_input(char *line, t_shell *shell)
{
	t_token	*toks;

	if (!line || !*line)
		return (NULL);
	if (has_unclosed_quotes(line))
	{
		ft_putstr_fd("minishell: syntax error: unclosed quotes\n", 2);
		shell->last_status = 2;
		return (NULL);
	}
	toks = lexer(line);
	if (!toks)
		return (NULL);
	return (parse_tokens(toks, shell));
}
