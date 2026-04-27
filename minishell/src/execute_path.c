/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:15:17 by elino             #+#    #+#             */
/*   Updated: 2026/03/25 10:55:19 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_path_components(char *argv0, t_shell *shell)
{
	char		*tmp;
	char		*slash;
	struct stat	st;

	tmp = ft_strdup(argv0);
	if (!tmp)
		child_exit(shell, 1);
	slash = tmp;
	slash = ft_strchr(slash, '/');
	while (slash)
	{
		*slash = '\0';
		if (*tmp && stat(tmp, &st) == 0 && !S_ISDIR(st.st_mode))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(argv0, 2);
			ft_putstr_fd(": Not a directory\n", 2);
			free(tmp);
			child_exit(shell, 126);
		}
		*slash = '/';
		slash++;
		slash = ft_strchr(slash, '/');
	}
	free(tmp);
}

static char	*resolve_abs(t_cmd *cmd, t_shell *shell)
{
	check_path_components(cmd->argv[0], shell);
	if (access(cmd->argv[0], F_OK) != 0)
		return (perror("minishell"), child_exit(shell, 127), NULL);
	if (access(cmd->argv[0], X_OK) != 0)
		return (perror("minishell"), child_exit(shell, 126), NULL);
	return (ft_strdup(cmd->argv[0]));
}

static char	*resolve_rel(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	path = resolve_path(cmd->argv[0], shell);
	if (!path)
	{
		print_path_err(cmd->argv[0], shell);
		child_exit(shell, 127);
	}
	if (access(path, X_OK) != 0)
	{
		perror("minishell");
		free(path);
		child_exit(shell, 126);
	}
	return (path);
}

void	exec_external(t_cmd *cmd, t_shell *shell)
{
	char		**envp;
	char		*path;
	struct stat	st;

	if (ft_strchr(cmd->argv[0], '/'))
		path = resolve_abs(cmd, shell);
	else
		path = resolve_rel(cmd, shell);
	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		free(path);
		child_exit(shell, 126);
	}
	envp = env_to_envp(shell->env);
	execve(path, cmd->argv, envp);
	perror("minishell");
	free(envp);
	free(path);
	child_exit(shell, 126);
}
