/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:15:17 by elino             #+#    #+#             */
/*   Updated: 2026/03/25 10:55:19 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_child_fds(int prev_fd, int *pipefd)
{
	if (prev_fd != -1)
		dup2(prev_fd, STDIN_FILENO);
	if (pipefd)
		dup2(pipefd[1], STDOUT_FILENO);
	if (prev_fd != -1)
		close(prev_fd);
	if (pipefd)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

int	run_pipeline(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*cur;
	int		prev_fd;
	pid_t	last_pid;
	int		ret;

	cur = cmds;
	prev_fd = -1;
	last_pid = -1;
	signal(SIGINT, SIG_IGN);
	while (cur)
	{
		if (fork_one(cur, shell, &prev_fd, &last_pid))
		{
			setup_signals_parent();
			return (1);
		}
		cur = cur->next;
	}
	close_heredoc_fds(cmds);
	ret = collect_status(last_pid);
	setup_signals_parent();
	return (ret);
}

int	exec_parent_builtin(t_cmd *cmd, t_shell *shell)
{
	int	saved_in;
	int	saved_out;
	int	ret;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (apply_redirs(cmd->redirs) != 0)
	{
		close(saved_in);
		close(saved_out);
		close_heredoc_fds(cmd);
		return (1);
	}
	ret = exec_builtin(cmd, shell);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
	close_heredoc_fds(cmd);
	return (ret);
}
