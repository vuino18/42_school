/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   revrotate_ops.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:13:20 by elino             #+#    #+#             */
/*   Updated: 2025/10/30 15:09:07 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_stack *a)
{
	t_node	*temp;

	if (a->size < 2)
		return ;
	temp = a->bottom;
	a->bottom = a->bottom->prev;
	a->bottom->next = NULL;
	temp->prev = NULL;
	temp->next = a->top;
	a->top->prev = temp;
	a->top = temp;
	write(1, "rra\n", 4);
}

void	rrb(t_stack *b)
{
	t_node	*temp;

	if (b->size < 2)
		return ;
	temp = b->bottom;
	b->bottom = b->bottom->prev;
	b->bottom->next = NULL;
	temp->prev = NULL;
	temp->next = b->top;
	b->top->prev = temp;
	b->top = temp;
	write(1, "rrb\n", 4);
}

void	rrr(t_stack *a, t_stack *b)
{
	t_node	*temp;

	if (a->size >= 2 && b->size >= 2)
	{
		temp = a->bottom;
		a->bottom = a->bottom->prev;
		a->bottom->next = NULL;
		temp->prev = NULL;
		temp->next = a->top;
		a->top->prev = temp;
		a->top = temp;
		temp = b->bottom;
		b->bottom = b->bottom->prev;
		b->bottom->next = NULL;
		temp->prev = NULL;
		temp->next = b->top;
		b->top->prev = temp;
		b->top = temp;
		write(1, "rrr\n", 4);
	}
	else if (a->size >= 2)
		rra(a);
	else if (b->size >= 2)
		rrb(b);
}
