/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 10:54:03 by elino             #+#    #+#             */
/*   Updated: 2026/03/25 10:54:05 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_name(char *name)
{
	int	i;

	if (!name || !name[0])
		return (0);
	if (name[0] != '_' && !(name[0] >= 'a' && name[0] <= 'z')
		&& !(name[0] >= 'A' && name[0] <= 'Z'))
		return (0);
	i = 1;
	while (name[i])
	{
		if (name[i] != '_' && !(name[i] >= 'a' && name[i] <= 'z')
			&& !(name[i] >= 'A' && name[i] <= 'Z')
			&& !(name[i] >= '0' && name[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

static void	remove_env(t_shell *shell, char *key)
{
	t_env	*current;
	t_env	*prev;

	current = shell->env;
	prev = NULL;
	while (current)
	{
		if (!ft_strcmp(current->key, key))
		{
			if (prev)
				prev->next = current->next;
			else
				shell->env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	builtin_unset(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	while (cmd->argv[i])
	{
		if (!is_valid_name(cmd->argv[i]))
		{
			ft_putstr_fd("minishell: unset: '", 2);
			ft_putstr_fd(cmd->argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			ret = 1;
		}
		else
			remove_env(shell, cmd->argv[i]);
		i++;
	}
	return (ret);
}
