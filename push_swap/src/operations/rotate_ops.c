/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:13:28 by elino             #+#    #+#             */
/*   Updated: 2025/10/30 15:11:13 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(t_stack *a)
{
	t_node	*temp;

	if (a->size < 2)
		return ;
	temp = a->top;
	a->top = a->top->next;
	a->top->prev = NULL;
	temp->next = NULL;
	temp->prev = a->bottom;
	a->bottom->next = temp;
	a->bottom = temp;
	write(1, "ra\n", 3);
}

void	rb(t_stack *b)
{
	t_node	*temp;

	if (b->size < 2)
		return ;
	temp = b->top;
	b->top = b->top->next;
	b->top->prev = NULL;
	temp->next = NULL;
	temp->prev = b->bottom;
	b->bottom->next = temp;
	b->bottom = temp;
	write(1, "rb\n", 3);
}

void	rr(t_stack *a, t_stack *b)
{
	t_node	*temp;

	if (a->size >= 2 && b->size >= 2)
	{
		temp = a->top;
		a->top = a->top->next;
		a->top->prev = NULL;
		temp->next = NULL;
		temp->prev = a->bottom;
		a->bottom->next = temp;
		a->bottom = temp;
		temp = b->top;
		b->top = b->top->next;
		b->top->prev = NULL;
		temp->next = NULL;
		temp->prev = b->bottom;
		b->bottom->next = temp;
		b->bottom = temp;
		write(1, "rr\n", 3);
	}
	else if (a->size >= 2)
		ra(a);
	else if (b->size >= 2)
		rb(b);
}
