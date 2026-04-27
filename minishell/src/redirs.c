/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 10:55:57 by elino             #+#    #+#             */
/*   Updated: 2026/03/25 10:55:58 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	handle_output(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(file);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	handle_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(file);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

void	apply_heredoc(t_redir *redir)
{
	if (redir->pipefd == -1)
		return ;
	dup2(redir->pipefd, STDIN_FILENO);
	close(redir->pipefd);
	redir->pipefd = -1;
}

int	apply_redirs(t_redir *redirs)
{
	while (redirs)
	{
		if (redirs->type == T_REDIR_IN)
		{
			if (handle_input(redirs->file))
				return (1);
		}
		else if (redirs->type == T_REDIR_OUT)
		{
			if (handle_output(redirs->file))
				return (1);
		}
		else if (redirs->type == T_REDIR_APPEND)
		{
			if (handle_append(redirs->file))
				return (1);
		}
		else if (redirs->type == T_HEREDOC)
			apply_heredoc(redirs);
		redirs = redirs->next;
	}
	return (0);
}
