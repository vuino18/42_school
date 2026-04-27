/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:13:54 by elino             #+#    #+#             */
/*   Updated: 2025/10/30 15:14:38 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_stack *a)
{
	int	temp;

	if (a->size < 2)
		return ;
	temp = a->top->value;
	a->top->value = a->top->next->value;
	a->top->next->value = temp;
	write(1, "sa\n", 3);
}

void	sb(t_stack *b)
{
	int	temp;

	if (b->size < 2)
		return ;
	temp = b->top->value;
	b->top->value = b->top->next->value;
	b->top->next->value = temp;
	write(1, "sb\n", 3);
}

void	ss(t_stack *a, t_stack *b)
{
	int	tmp;

	if (a->size >= 2 && b->size >= 2)
	{
		tmp = a->top->value;
		a->top->value = a->top->next->value;
		a->top->next->value = tmp;
		tmp = b->top->value;
		b->top->value = b->top->next->value;
		b->top->next->value = tmp;
		write(1, "ss\n", 3);
	}
	else if (a->size >= 2)
		sa(a);
	else if (b->size >= 2)
		sb(b);
}
