/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 10:52:52 by elino             #+#    #+#             */
/*   Updated: 2026/04/07 09:47:06 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd(t_shell *shell)
{
	char	buf[4096];
	char	*old;

	old = get_env_value(shell->env, "PWD");
	if (old)
		set_env_value(&shell->env, "OLDPWD", old);
	if (getcwd(buf, sizeof(buf)))
		set_env_value(&shell->env, "PWD", buf);
}

static int	cd_chdir_err(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

static int get_cmd_args(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->argv[i])
		i++;
	return (i);
}

static int	cd_get_path(t_cmd *cmd, t_shell *shell, char **path)
{
	int	ac;

	ac = get_cmd_args(cmd);
	if (ac > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (!cmd->argv[1])
	{
		*path = get_env_value(shell->env, "HOME");
		if (!*path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
	}
	else
		*path = cmd->argv[1];
	return (0);
}

int	builtin_cd(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	path = NULL;
	if (cd_get_path(cmd, shell, &path))
		return (1);
	if (chdir(path) == -1)
		return (cd_chdir_err(path));
	update_pwd(shell);
	return (0);
}
