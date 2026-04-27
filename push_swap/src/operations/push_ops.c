/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 14:58:47 by elino             #+#    #+#             */
/*   Updated: 2025/10/30 14:58:53 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pa(t_stack *a, t_stack *b)
{
	t_node	*temp;

	if (b->size == 0)
		return ;
	temp = b->top;
	b->top = b->top->next;
	if (b->top)
		b->top->prev = NULL;
	else
		b->bottom = NULL;
	temp->next = a->top;
	temp->prev = NULL;
	if (a->top)
		a->top->prev = temp;
	else
		a->bottom = temp;
	a->top = temp;
	a->size++;
	b->size--;
	write(1, "pa\n", 3);
}

void	pb(t_stack *a, t_stack *b)
{
	t_node	*temp;

	if (a->size == 0)
		return ;
	temp = a->top;
	a->top = a->top->next;
	if (a->top)
		a->top->prev = NULL;
	else
		a->bottom = NULL;
	temp->next = b->top;
	temp->prev = NULL;
	if (b->top)
		b->top->prev = temp;
	else
		b->bottom = temp;
	b->top = temp;
	a->size--;
	b->size++;
	write(1, "pb\n", 3);
}
