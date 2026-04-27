/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:32:36 by elino             #+#    #+#             */
/*   Updated: 2025/10/31 13:12:06 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	process_number(t_stack *stack, char *str)
{
	long	num;
	int		is_valid;

	num = ft_atoi_safe(str, &is_valid);
	if (!is_valid || num < INT_MIN || num > INT_MAX)
		return (0);
	push_value(stack, (int)num);
	return (1);
}

static int	process_split(t_stack *stack, char **split)
{
	int	j;

	j = 0;
	while (split[j])
		j++;
	while (--j >= 0)
	{
		if (!process_number(stack, split[j]))
			return (0);
	}
	return (1);
}

static int	fill_stack(t_stack *stack, int argc, char **argv)
{
	int		i;
	char	**split;

	i = argc - 1;
	while (i > 0)
	{
		split = ft_split(argv[i], ' ');
		if (!split)
			return (0);
		if (!process_split(stack, split))
			return (free_split(split), 0);
		free_split(split);
		i--;
	}
	return (1);
}

t_stack	*stack_init(int argc, char **argv)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->top = NULL;
	stack->bottom = NULL;
	stack->size = 0;
	if (!fill_stack(stack, argc, argv))
		return (free_stack(stack), NULL);
	assign_indexes(stack);
	return (stack);
}
