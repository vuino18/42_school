/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 09:56:02 by elino             #+#    #+#             */
/*   Updated: 2025/11/27 12:23:48 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exit_with_errno(char **args, char *path)
{
	if (errno == EACCES)
	{
		free_array(args);
		free(path);
		exit(126);
	}
	if (errno == ENOENT)
	{
		free_array(args);
		free(path);
		exit(127);
	}
	free_array(args);
	free(path);
	exit(1);
}

void	child_exec(char *cmd, char **envp)
{
	char	**args;
	char	*path;

	args = parse_command(cmd);
	if (!args || !args[0])
	{
		free_array(args);
		exit(127);
	}
	path = find_command_path(args[0], envp);
	if (!path)
	{
		write(2, "pipex:  ", 7);
		write(2, args[0], ft_strlen(args[0]));
		write(2, ": command not found\n", 21);
		free_array(args);
		exit(127);
	}
	execve(path, args, envp);
	write(2, "pipex:  ", 7);
	perror(NULL);
	exit_with_errno(args, path);
}
