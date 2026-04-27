/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:34:07 by alcarval          #+#    #+#             */
/*   Updated: 2026/04/09 15:34:09 by alcarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_init(char **envp)
{
	t_env	*head;
	t_env	*node;
	char	*eq;
	char	*key;

	head = NULL;
	while (envp && *envp)
	{
		eq = ft_strchr(*envp, '=');
		if (eq)
		{
			key = ft_substr(*envp, 0, eq - *envp);
			node = new_env_node(key, eq + 1);
			free(key);
		}
		else
			node = new_env_node(*envp, NULL);
		if (node)
			append_node(&head, node);
		envp++;
	}
	return (head);
}

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	set_env_value(t_env **head, char *key, char *value)
{
	t_env	*cur;
	t_env	*node;

	cur = *head;
	while (cur)
	{
		if (!ft_strcmp(cur->key, key))
		{
			free(cur->value);
			if (value)
				cur->value = ft_strdup(value);
			else
				cur->value = NULL;
			return ;
		}
		cur = cur->next;
	}
	node = new_env_node(key, value);
	if (node)
		append_node(head, node);
}
