/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:36:43 by alcarval          #+#    #+#             */
/*   Updated: 2026/04/09 15:36:44 by alcarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint_line(t_shell *shell)
{
	g_signal = 0;
	shell->last_status = 130;
	rl_on_new_line();
}

static void	handle_no_line(t_shell *shell)
{
	if (g_signal == SIGINT)
	{
		g_signal = 0;
		shell->last_status = 130;
	}
	ft_putstr_fd("exit\n", 1);
}

int	line_needs_more(char *line)
{
	int	i;
	int	state;
	int	last_pipe;
	int	seen_word;

	if (!line || !*line)
		return (0);
	i = 0;
	state = 0;
	last_pipe = 0;
	seen_word = 0;
	while (line[i])
	{
		state = lnm_update_quote(state, line[i]);
		if (state != 0)
			seen_word = 1;
		else
			lnm_handle_pipe(line, &i, &last_pipe, &seen_word);
		i++;
	}
	if (state != 0)
		return (0);
	return (last_pipe);
}

char	*read_full_line(char *first, t_shell *shell)
{
	char	*cont;
	char	*joined;

	joined = first;
	while (line_needs_more(joined))
	{
		cont = readline("> ");
		if (!cont)
			return (free(joined), NULL);
		if (g_signal == SIGINT)
		{
			handle_sigint_line(shell);
			free(cont);
			free(joined);
			return (NULL);
		}
		joined = rfl_join(joined, cont);
		if (!joined)
			return (NULL);
	}
	return (joined);
}

void	shell_loop(t_shell *shell)
{
	char	*line;

	while (shell->running)
	{
		g_signal = 0;
		setup_signals_parent();
		line = readline("minishell$ ");
		if (!line)
		{
			handle_no_line(shell);
			break ;
		}
		loop_iter(shell, line);
	}
	rl_clear_history();
}
