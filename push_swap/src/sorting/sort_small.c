/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:16:21 by elino             #+#    #+#             */
/*   Updated: 2025/10/30 15:27:17 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_two(t_stack *a)
{
	t_node	*top;

	if (!a || a->size < 2)
		return ;
	top = a->top;
	if (top->value > top->next->value)
		sa(a);
}

void	sort_three(t_stack *a)
{
	int	top;
	int	middle;
	int	bottom;

	if (a->size < 3)
		return ;
	top = a->top->value;
	middle = a->top->next->value;
	bottom = a->bottom->value;
	if (top > middle && middle < bottom && top < bottom)
		sa(a);
	else if (top > middle && middle > bottom)
	{
		sa(a);
		rra(a);
	}
	else if (top > middle && middle < bottom && top > bottom)
		ra(a);
	else if (top < middle && middle > bottom && top < bottom)
	{
		sa(a);
		ra(a);
	}
	else if (top < middle && middle > bottom && top > bottom)
		rra(a);
}

void	sort_five(t_stack *a, t_stack *b)
{
	move_min_to_top(a);
	pb(a, b);
	move_min_to_top(a);
	pb(a, b);
	sort_three(a);
	pa(a, b);
	pa(a, b);
}
