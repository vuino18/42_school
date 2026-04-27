/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:35:01 by alcarval          #+#    #+#             */
/*   Updated: 2026/04/09 15:35:03 by alcarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	decode_signal_exit(int last_status)
{
	if (WTERMSIG(last_status) == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	else if (WTERMSIG(last_status) == SIGQUIT)
		write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
	return (128 + WTERMSIG(last_status));
}

int	collect_status(pid_t last_pid)
{
	int		status;
	int		last_status;
	pid_t	wpid;

	last_status = 0;
	while (1)
	{
		wpid = wait(&status);
		if (wpid == -1)
			break ;
		if (wpid == last_pid)
			last_status = status;
	}
	g_signal = 0;
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	if (WIFSIGNALED(last_status))
		return (decode_signal_exit(last_status));
	return (1);
}

static void	update_fds(int *prev_fd, int *pipefd, int has_next)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	*prev_fd = -1;
	if (has_next)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
}

static void	dispatch_child(t_cmd *cur, t_shell *shell, int prev_fd, int *pfd)
{
	if (cur->next)
		run_child(cur, shell, prev_fd, pfd);
	else
		run_child(cur, shell, prev_fd, NULL);
}

int	fork_one(t_cmd *cur, t_shell *shell, int *prev_fd, pid_t *last_pid)
{
	int		pipefd[2];
	pid_t	pid;

	if (cur->next && pipe(pipefd) == -1)
	{
		perror("minishell: pipe");
		return (1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		if (cur->next)
			close_pipes(pipefd);
		return (1);
	}
	if (pid == 0)
		dispatch_child(cur, shell, *prev_fd, pipefd);
	*last_pid = pid;
	update_fds(prev_fd, pipefd, cur->next != NULL);
	return (0);
}
