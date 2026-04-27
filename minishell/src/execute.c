/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:15:17 by elino             #+#    #+#             */
/*   Updated: 2026/03/25 10:55:19 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_parent_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	exec_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (builtin_echo(cmd, shell));
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (builtin_pwd(cmd, shell));
	if (!ft_strcmp(cmd->argv[0], "env"))
		return (builtin_env(cmd, shell));
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return (builtin_cd(cmd, shell));
	if (!ft_strcmp(cmd->argv[0], "export"))
		return (builtin_export(cmd, shell));
	if (!ft_strcmp(cmd->argv[0], "unset"))
		return (builtin_unset(cmd, shell));
	if (!ft_strcmp(cmd->argv[0], "exit"))
		return (builtin_exit(cmd, shell));
	return (1);
}

void	child_exit(t_shell *shell, int code)
{
	rl_clear_history();
	free_cmds(shell->cmds);
	free_env(shell->env);
	exit(code);
}

void	run_child(t_cmd *cmd, t_shell *shell, int prev_fd, int *pipefd)
{
	int	ret;

	setup_signals_child();
	setup_child_fds(prev_fd, pipefd);
	if (apply_redirs(cmd->redirs) != 0)
		child_exit(shell, 1);
	if (cmd->argv && cmd->argv[0] && is_builtin(cmd->argv[0]))
	{
		ret = exec_builtin(cmd, shell);
		child_exit(shell, ret);
	}
	if (!cmd->argv || !cmd->argv[0])
		child_exit(shell, 0);
	exec_external(cmd, shell);
}

int	execute_pipeline(t_cmd *cmds, t_shell *shell)
{
	if (prepare_heredocs(cmds, shell))
	{
		g_signal = 0;
		shell->last_status = 130;
		return (130);
	}
	if (cmds && !cmds->next && cmds->argv && cmds->argv[0]
		&& is_parent_builtin(cmds->argv[0]))
		return (exec_parent_builtin(cmds, shell));
	return (run_pipeline(cmds, shell));
}
