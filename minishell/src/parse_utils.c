/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:36:28 by alcarval          #+#    #+#             */
/*   Updated: 2026/04/09 15:36:30 by alcarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*new_redir(t_token_type type, char *file)
{
	t_redir			*r;
	t_redir_type	rtype;

	rtype = T_REDIR_IN;
	if (type == TOK_REDIR_OUT)
		rtype = T_REDIR_OUT;
	else if (type == TOK_REDIR_APPEND)
		rtype = T_REDIR_APPEND;
	else if (type == TOK_HEREDOC)
		rtype = T_HEREDOC;
	r = malloc(sizeof(t_redir));
	if (!r)
		return (NULL);
	r->type = rtype;
	r->file = ft_strdup(file);
	r->pipefd = -1;
	r->quoted = 0;
	r->next = NULL;
	if (!r->file)
		return (free(r), NULL);
	return (r);
}

static void	free_redir_list(t_redir *r)
{
	t_redir	*next;

	while (r)
	{
		next = r->next;
		if (r->pipefd != -1)
			close(r->pipefd);
		free(r->file);
		free(r);
		r = next;
	}
}

static void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*next;

	while (cmds)
	{
		next = cmds->next;
		free_argv(cmds->argv);
		free_redir_list(cmds->redirs);
		free(cmds);
		cmds = next;
	}
}
