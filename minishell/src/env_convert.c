/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:33:53 by alcarval          #+#    #+#             */
/*   Updated: 2026/04/09 15:33:55 by alcarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*make_env_str(char *key, char *value)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, value);
	free(tmp);
	return (result);
}

static void	free_envp(char **envp, int i)
{
	while (i > 0)
	{
		i--;
		free(envp[i]);
	}
	free(envp);
}

static int	count_with_value(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		if (env->value)
			count++;
		env = env->next;
	}
	return (count);
}

static char	**fill_envp(char **envp, t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (env->value)
		{
			envp[i] = make_env_str(env->key, env->value);
			if (!envp[i])
				return (free_envp(envp, i), NULL);
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	**env_to_envp(t_env *env)
{
	char	**envp;

	envp = malloc(sizeof(char *) * (count_with_value(env) + 1));
	if (!envp)
		return (NULL);
	return (fill_envp(envp, env));
}
