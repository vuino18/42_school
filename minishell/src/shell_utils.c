/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:36:43 by alcarval          #+#    #+#             */
/*   Updated: 2026/04/09 15:36:44 by alcarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_line(t_shell *shell, char *line)
{
	t_cmd	*cmds;
	int		status;

	cmds = parse_input(line, shell);
	free(line);
	if (!cmds)
		return (shell->last_status);
	shell->cmds = cmds;
	status = execute_pipeline(cmds, shell);
	shell->cmds = NULL;
	free_cmds(cmds);
	return (status);
}

void	lnm_handle_pipe(char *line, int *i, int *last_pipe, int *seen_word)
{
	if (line[*i] == '|' && line[*i + 1] == '|')
	{
		*last_pipe = 0;
		*seen_word = 0;
		(*i)++;
	}
	else if (line[*i] == '|')
		*last_pipe = *seen_word;
	else if (line[*i] != ' ' && line[*i] != '\t' && line[*i] != '\n')
	{
		*seen_word = 1;
		*last_pipe = 0;
	}
}

int	lnm_update_quote(int state, char c)
{
	if (c == '\'' && state == 0)
		return (1);
	if (c == '\'' && state == 1)
		return (0);
	if (c == '"' && state == 0)
		return (2);
	if (c == '"' && state == 2)
		return (0);
	return (state);
}

char	*rfl_join(char *joined, char *cont)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(joined, "\n");
	free(joined);
	if (!tmp)
		return (free(cont), NULL);
	result = ft_strjoin(tmp, cont);
	free(tmp);
	free(cont);
	return (result);
}

void	loop_iter(t_shell *shell, char *line)
{
	char	*full;

	if (g_signal == SIGINT)
	{
		shell->last_status = 130;
		g_signal = 0;
	}
	if (!*line)
		return (free(line));
	full = read_full_line(line, shell);
	if (!full)
	{
		if (g_signal == SIGINT)
		{
			shell->last_status = 130;
			g_signal = 0;
		}
		return ;
	}
	add_history(full);
	shell->last_status = process_line(shell, full);
}
