/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_build.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:35:27 by alcarval          #+#    #+#             */
/*   Updated: 2026/04/21 11:57:13 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_word(t_cmd *cmd, char *word)
{
	char	**nargv;
	int		len;
	int		i;

	if (!word || word[0] == '\0')
		return (1);
	len = 0;
	while (cmd->argv && cmd->argv[len])
		len++;
	nargv = malloc(sizeof(char *) * (len + 2));
	if (!nargv)
		return (1);
	i = 0;
	while (i < len)
	{
		nargv[i] = cmd->argv[i];
		i++;
	}
	nargv[len] = ft_strdup(word);
	nargv[len + 1] = NULL;
	if (!nargv[len])
		return (free(nargv), 1);
	free(cmd->argv);
	cmd->argv = nargv;
	return (0);
}

static void	append_redir(t_cmd *cmd, t_redir *redir)
{
	t_redir	*tail;

	if (!cmd->redirs)
	{
		cmd->redirs = redir;
		return ;
	}
	tail = cmd->redirs;
	while (tail->next)
		tail = tail->next;
	tail->next = redir;
}

static int	add_redir(t_cmd *cmd, t_token **cur)
{
	t_redir	*redir;

	if (!(*cur)->next || (*cur)->next->type != TOK_WORD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (!(*cur)->next)
			ft_putstr_fd("newline", 2);
		else
			ft_putstr_fd((char *)tok_name((*cur)->next), 2);
		ft_putstr_fd("'\n", 2);
		return (1);
	}
	if (!(*cur)->next->value)
		return (1);
	redir = new_redir((*cur)->type, (*cur)->next->value);
	if (!redir)
		return (1);
	*cur = (*cur)->next;
	redir->quoted = (*cur)->quoted;
	append_redir(cmd, redir);
	return (0);
}

static t_cmd	*build_cmd(t_token **cur)
{
	t_cmd	*cmd;

	cmd = new_cmd();
	if (!cmd)
		return (NULL);
	while (*cur && (*cur)->type != TOK_PIPE && (*cur)->type != TOK_OR)
	{
		if ((*cur)->type == TOK_WORD)
		{
			if (add_word(cmd, (*cur)->value))
				return (free_cmds(cmd), NULL);
		}
		else if (add_redir(cmd, cur))
			return (free_cmds(cmd), NULL);
		*cur = (*cur)->next;
	}
	return (cmd);
}

t_cmd	*build_pipeline(t_token *toks)
{
	t_cmd	*head;
	t_cmd	*tail;
	t_cmd	*cmd;
	t_token	*cur;

	head = NULL;
	tail = NULL;
	cur = toks;
	while (cur)
	{
		cmd = build_cmd(&cur);
		if (!cmd)
			return (free_cmds(head), NULL);
		if (!head)
			head = cmd;
		else
			tail->next = cmd;
		tail = cmd;
		if (cur)
			cur = cur->next;
	}
	return (head);
}
