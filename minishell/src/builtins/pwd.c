/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 10:53:49 by elino             #+#    #+#             */
/*   Updated: 2026/03/25 10:53:55 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_cmd *cmd, t_shell *shell)
{
	char	buffer[4096];

	(void)cmd;
	(void)shell;
	if (!getcwd(buffer, sizeof(buffer)))
	{
		perror("minishell: pwd");
		return (1);
	}
	ft_putstr_fd(buffer, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}
