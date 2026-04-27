/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 10:53:27 by elino             #+#    #+#             */
/*   Updated: 2026/03/25 10:53:29 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_bad_arg(t_cmd *cmd, t_shell *shell, char *arg)
{
	if (!is_numeric(arg))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		shell->running = 0;
		return (2);
	}
	if (cmd->argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (is_overflow(arg))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		shell->running = 0;
		return (2);
	}
	return (-1);
}

int	builtin_exit(t_cmd *cmd, t_shell *shell)
{
	char	*arg;
	int		ret;

	ft_putstr_fd("exit\n", 1);
	if (!cmd->argv[1])
	{
		ret = shell->last_status;
		shell->running = 0;
		return (ret);
	}
	arg = cmd->argv[1];
	while (*arg == ' ')
		arg++;
	ret = exit_bad_arg(cmd, shell, arg);
	if (ret != -1)
		return (ret);
	shell->running = 0;
	return (get_exit_code(arg));
}
