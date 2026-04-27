/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 10:56:06 by elino             #+#    #+#             */
/*   Updated: 2026/03/25 10:56:07 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_shell(t_shell *shell, char **envp)
{
	shell->env = env_init(envp);
	shell->last_status = 0;
	shell->running = 1;
	shell->cmds = NULL;
}

static void	cleanup_shell(t_shell *shell)
{
	free_env(shell->env);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	setup_signals_parent();
	shell_loop(&shell);
	cleanup_shell(&shell);
	return (shell.last_status);
}
