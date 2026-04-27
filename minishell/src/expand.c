/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:34:47 by alcarval          #+#    #+#             */
/*   Updated: 2026/04/09 15:34:49 by alcarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_free(char *a, char *b)
{
	char	*res;

	if (!b)
	{
		free(a);
		return (NULL);
	}
	res = ft_strjoin(a, b);
	free(a);
	free(b);
	return (res);
}

static int	update_state(int state, char c)
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

static char	*expand_name(char *s, int *i, t_shell *sh)
{
	int		j;
	char	*name;
	char	*val;

	j = *i;
	while (s[j] == '_' || (s[j] >= 'a' && s[j] <= 'z')
		|| (s[j] >= 'A' && s[j] <= 'Z')
		|| (s[j] >= '0' && s[j] <= '9'))
		j++;
	if (j == *i)
		return (ft_strdup("$"));
	name = ft_substr(s, *i, j - *i);
	*i = j;
	if (!name)
		return (ft_strdup(""));
	val = get_env_value(sh->env, name);
	free(name);
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val));
}

char	*expand_dollar(char *s, int *i, t_shell *sh)
{
	(*i)++;
	if (!s[*i])
		return (ft_strdup("$"));
	if (s[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(sh->last_status));
	}
	return (expand_name(s, i, sh));
}

char	*expand_word(char *s, t_shell *sh)
{
	char	*res;
	int		i;
	int		state;

	res = ft_strdup("");
	i = 0;
	state = 0;
	while (s && s[i] && res)
	{
		if (update_state(state, s[i]) != state)
		{
			state = update_state(state, s[i]);
			i++;
		}
		else if (state != 1 && s[i] == '$')
			res = join_free(res, expand_dollar(s, &i, sh));
		else
		{
			res = join_free(res, ft_substr(s, i, 1));
			i++;
		}
	}
	return (res);
}
