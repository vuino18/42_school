/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:46:17 by elino             #+#    #+#             */
/*   Updated: 2025/11/22 15:55:40 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**split_paths(char *path_env)
{
	if (!path_env)
		return (NULL);
	return (ft_split(path_env, ':'));
}

char	*get_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*check_direct_path(char *cmd)
{
	char	*full;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
		{
			full = ft_strdup(cmd);
			return (full);
		}
		return (NULL);
	}
	return (NULL);
}

static char	*search_in_paths(char *cmd, char **envp)
{
	char	**paths;
	char	*full;
	int		i;

	paths = split_paths(get_path_env(envp));
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full = join_three(paths[i], "/", cmd);
		if (!full)
			return (free_array(paths), NULL);
		if (access(full, F_OK) == 0)
			return (free_array(paths), full);
		free(full);
		i++;
	}
	free_array(paths);
	return (NULL);
}

char	*find_command_path(char *cmd, char **envp)
{
	char	*direct;

	direct = check_direct_path(cmd);
	if (direct)
		return (direct);
	return (search_in_paths(cmd, envp));
}
