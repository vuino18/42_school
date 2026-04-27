/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 10:53:35 by elino             #+#    #+#             */
/*   Updated: 2026/03/25 10:53:40 by elino            ###   ########.fr       */
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

static void	print_one(t_env *node)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(node->key, 1);
	if (node->value)
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(node->value, 1);
		ft_putchar_fd('"', 1);
	}
	ft_putchar_fd('\n', 1);
}

static void	print_export(t_shell *shell)
{
	t_env	*cur;
	t_env	*min;
	t_env	*last;

	last = NULL;
	while (1)
	{
		cur = shell->env;
		min = NULL;
		while (cur)
		{
			if (!last || ft_strcmp(cur->key, last->key) > 0)
				if (!min || ft_strcmp(cur->key, min->key) < 0)
					min = cur;
			cur = cur->next;
		}
		if (!min || (last && ft_strcmp(min->key, last->key) <= 0))
			break ;
		print_one(min);
		last = min;
	}
}

static int	process_arg(t_shell *shell, char *arg)
{
	char	*equal;
	char	*key;

	equal = ft_strchr(arg, '=');
	if (equal)
		key = ft_substr(arg, 0, equal - arg);
	else
		key = ft_strdup(arg);
	if (!key)
		return (1);
	if (!is_valid_name(key))
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		free(key);
		return (1);
	}
	if (equal)
		set_env_value(&shell->env, key, equal + 1);
	else
		set_env_value(&shell->env, key, NULL);
	free(key);
	return (0);
}

int	builtin_export(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	ret;

	if (!cmd->argv[1])
	{
		print_export(shell);
		return (0);
	}
	i = 1;
	ret = 0;
	while (cmd->argv[i])
	{
		if (process_arg(shell, cmd->argv[i]))
			ret = 1;
		i++;
	}
	return (ret);
}
