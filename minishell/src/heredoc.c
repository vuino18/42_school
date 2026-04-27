/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 10:55:30 by elino             #+#    #+#             */
/*   Updated: 2026/04/07 10:51:10 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_heredoc_fds(t_cmd *cmds)
{
	t_cmd	*cmd;
	t_redir	*r;

	cmd = cmds;
	while (cmd)
	{
		r = cmd->redirs;
		while (r)
		{
			if (r->type == T_HEREDOC && r->pipefd != -1)
			{
				close(r->pipefd);
				r->pipefd = -1;
			}
			r = r->next;
		}
		cmd = cmd->next;
	}
}

static int	hd_check_signal(int fd0, int status)
{
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
	{
		write(STDOUT_FILENO, "\n", 1);
		g_signal = SIGINT;
		close(fd0);
		return (1);
	}
	return (0);
}

static pid_t	hd_fork(int fd[2], t_redir *redir, t_shell *sh)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (close(fd[0]), close(fd[1]), setup_signals_parent(), -1);
	if (pid == 0)
	{
		close(fd[0]);
		heredoc_child(fd[1], redir->file, redir->quoted, sh);
	}
	return (pid);
}

static int	open_heredoc(t_redir *redir, t_shell *sh)
{
	int				fd[2];
	pid_t			pid;
	int				status;
	struct termios	saved;

	tcgetattr(STDIN_FILENO, &saved);
	if (pipe(fd) == -1)
		return (perror("minishell: heredoc pipe"), 1);
	signal(SIGINT, SIG_IGN);
	pid = hd_fork(fd, redir, sh);
	if (pid == -1)
		return (1);
	close(fd[1]);
	waitpid(pid, &status, 0);
	tcsetattr(STDIN_FILENO, TCSANOW, &saved);
	setup_signals_parent();
	if (hd_check_signal(fd[0], status))
		return (1);
	redir->pipefd = fd[0];
	return (0);
}

int	prepare_heredocs(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*cmd;
	t_redir	*r;

	cmd = cmds;
	while (cmd)
	{
		r = cmd->redirs;
		while (r)
		{
			if (r->type == T_HEREDOC)
				if (open_heredoc(r, shell))
					return (1);
			r = r->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
