/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:37:49 by alcarval          #+#    #+#             */
/*   Updated: 2026/04/09 15:37:51 by alcarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_path_err(char *cmd, char *msg)
{
	char	*s;
	char	*tmp;

	s = ft_strjoin("minishell: ", cmd);
	if (!s)
		return ;
	tmp = ft_strjoin(s, msg);
	free(s);
	if (!tmp)
		return ;
	write(STDERR_FILENO, tmp, ft_strlen(tmp));
	free(tmp);
}

static char	*try_path(char *dir, char *cmd)
{
	char	*slash;
	char	*full;

	slash = ft_strjoin(dir, "/");
	if (!slash)
		return (NULL);
	full = ft_strjoin(slash, cmd);
	free(slash);
	if (!full)
		return (NULL);
	if (access(full, X_OK) == 0)
		return (full);
	free(full);
	return (NULL);
}

static char	*search_path(char *path_env, char *cmd)
{
	char	**dirs;
	char	*found;
	int		i;

	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (NULL);
	found = NULL;
	i = 0;
	while (dirs[i] && !found)
	{
		found = try_path(dirs[i], cmd);
		i++;
	}
	i = 0;
	while (dirs[i])
		free(dirs[i++]);
	free(dirs);
	return (found);
}

void	print_path_err(char *cmd, t_shell *shell)
{
	if (ft_strchr(cmd, '/') && access(cmd, F_OK) != 0)
		write_path_err(cmd, ": No such file or directory\n");
	else if (ft_strchr(cmd, '/'))
		write_path_err(cmd, ": Permission denied\n");
	else if (!get_env_value(shell->env, "PATH"))
		write_path_err(cmd, ": No such file or directory\n");
	else
		write_path_err(cmd, ": command not found\n");
}

char	*resolve_path(char *cmd, t_shell *shell)
{
	char	*path_env;

	if (!cmd || !cmd[0])
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = get_env_value(shell->env, "PATH");
	if (!path_env)
		return (NULL);
	return (search_path(path_env, cmd));
}
