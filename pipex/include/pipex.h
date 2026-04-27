/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 09:45:17 by elino             #+#    #+#             */
/*   Updated: 2025/11/22 09:47:17 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft.h"

void	child_exec(char *cmd, char **envp);
char	*find_command_path(char *cmd, char **envp);
char	**parse_command(char *cmd);
void	free_array(char **arr);
void	error_exit(char *msg);
void	close_all(int *p);
char	*join_three(char *a, char *b, char *c);
char	*get_path_env(char **envp);
void	close_pipe(int pipefd[2]);
void	wait_children(pid_t pid1, pid_t pid2);
void	handle_parent(int pipefd[2], pid_t pid1, pid_t pid2);
void	fatal_with_close(int *p, int fd, const char *msg);

#endif
