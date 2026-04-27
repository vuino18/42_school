/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 09:48:23 by elino             #+#    #+#             */
/*   Updated: 2025/11/28 15:28:19 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fatal_with_close(int *p, int fd, const char *msg)
{
	if (p)
	{
		close(p[0]);
		close(p[1]);
	}
	if (fd != -1)
		close(fd);
	perror(msg);
	exit(1);
}

static void	first(int *p, char **av, char **e)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		write(2, "pipex:  ", 7);
		perror(av[1]);
		close_all(p);
		exit(1);
	}
	if (dup2(fd, 0) == -1 || dup2(p[1], 1) == -1)
		fatal_with_close(p, fd, "dup2 failed");
	close(fd);
	close_all(p);
	child_exec(av[2], e);
}

static void	second(int *p, char **av, char **e)
{
	int	fd;

	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		write(2, "pipex:  ", 7);
		perror(av[4]);
		close_all(p);
		exit(1);
	}
	if (dup2(p[0], 0) == -1 || dup2(fd, 1) == -1)
		fatal_with_close(p, fd, "dup2 failed");
	close(fd);
	close_all(p);
	child_exec(av[3], e);
}

static void	run(int *p, char **av, char **e)
{
	pid_t	pid1;
	pid_t	pid2;

	pid1 = fork();
	if (pid1 == -1)
		fatal_with_close(p, -1, "fork error");
	if (!pid1)
		first(p, av, e);
	pid2 = fork();
	if (pid2 == -1)
		fatal_with_close(p, -1, "fork error");
	if (!pid2)
		second(p, av, e);
	handle_parent(p, pid1, pid2);
}

int	main(int argc, char **argv, char **envp)
{
	int	pipe_fd[2];

	if (argc != 5)
	{
		write(2, "use: ./pipex infile cmd1 cmd2 outfile\n", 41);
		return (1);
	}
	if (pipe(pipe_fd) == -1)
		fatal_with_close(NULL, -1, "pipe error");
	run(pipe_fd, argv, envp);
	return (1);
}
