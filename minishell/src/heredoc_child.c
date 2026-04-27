/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 10:55:30 by elino             #+#    #+#             */
/*   Updated: 2026/04/07 10:51:10 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_hd_line(char *s, t_shell *sh)
{
	char	*res;
	int		i;

	res = ft_strdup("");
	i = 0;
	while (s && s[i] && res)
	{
		if (s[i] == '$')
			res = join_free(res, expand_dollar(s, &i, sh));
		else
		{
			res = join_free(res, ft_substr(s, i, 1));
			i++;
		}
	}
	return (res);
}

static void	hd_clean_exit(int wfd, t_shell *sh, int code)
{
	close(wfd);
	rl_clear_history();
	free_cmds(sh->cmds);
	free_env(sh->env);
	exit(code);
}

static void	handle_sigint_hd(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	close(STDIN_FILENO);
}

static void	hd_write_line(int wfd, char *line, int quoted, t_shell *sh)
{
	char	*out;

	out = line;
	if (!quoted && sh)
		out = expand_hd_line(line, sh);
	ft_putstr_fd(out, wfd);
	ft_putchar_fd('\n', wfd);
	if (!quoted && sh)
		free(out);
	free(line);
}

void	heredoc_child(int wfd, char *delim, int quoted, t_shell *sh)
{
	char	*line;

	rl_catch_signals = 1;
	signal(SIGINT, handle_sigint_hd);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (g_signal == SIGINT)
			return (free(line), hd_clean_exit(wfd, sh, 130));
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document"
				" delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(delim, 2);
			ft_putstr_fd("')\n", 2);
			hd_clean_exit(wfd, sh, 0);
		}
		if (!ft_strcmp(line, delim))
			return (free(line), hd_clean_exit(wfd, sh, 0));
		hd_write_line(wfd, line, quoted, sh);
	}
}
