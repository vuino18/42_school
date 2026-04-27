/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:39:33 by elino             #+#    #+#             */
/*   Updated: 2025/10/30 15:57:16 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_min(t_stack *a)
{
	t_node	*current;
	int		min;

	current = a->top;
	min = current->value;
	while (current)
	{
		if (current->value < min)
			min = current->value;
		current = current->next;
	}
	return (min);
}

int	get_index(t_stack *a, int value)
{
	t_node	*current;
	int		index;

	current = a->top;
	index = 0;
	while (current)
	{
		if (current->value == value)
			return (index);
		index++;
		current = current->next;
	}
	return (-1);
}

void	move_min_to_top(t_stack *a)
{
	int	min;
	int	index;

	min = get_min(a);
	index = get_index(a, min);
	if (index <= a->size / 2)
	{
		while (index-- > 0)
			ra(a);
	}
	else
	{
		index = a->size - index;
		while (index-- > 0)
			rra(a);
	}
}

int	get_max_index(t_stack *stack)
{
	t_node	*current;
	int		max;

	if (!stack || !stack->top)
		return (-1);
	current = stack->top;
	max = current->index;
	while (current)
	{
		if (current->index > max)
			max = current->index;
		current = current->next;
	}
	return (max);
}

void	move_max_to_top(t_stack *b, int max_index)
{
	t_node	*current;
	int		pos;
	int		i;

	if (!b || b->size < 2)
		return ;
	current = b->top;
	pos = 0;
	while (current && current->index != max_index)
	{
		current = current->next;
		pos++;
	}
	if (pos <= b->size / 2)
	{
		i = 0;
		while (i++ < pos)
			rb(b);
	}
	else
	{
		i = 0;
		while (i++ < b->size - pos)
			rrb(b);
	}
}
