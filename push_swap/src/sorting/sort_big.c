/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_big.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:27:52 by elino             #+#    #+#             */
/*   Updated: 2025/10/30 15:28:46 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_chunk_count(int size)
{
	if (size <= 100)
		return (5);
	else if (size <= 500)
		return (11);
	return (20);
}

static void	push_chunks(t_stack *a, t_stack *b, int chunk_count)
{
	int	chunk_size;
	int	chunk_limit;
	int	i;

	chunk_size = a->size / chunk_count;
	chunk_limit = chunk_size;
	i = 0;
	while (a->size > 0)
	{
		if (a->top->index < chunk_limit)
		{
			pb(a, b);
			i++;
			if (b->top->index < chunk_limit - (chunk_size / 2))
				rb(b);
			if (i == chunk_limit)
				chunk_limit += chunk_size;
		}
		else
			ra(a);
	}
}

static void	push_back_sorted(t_stack *a, t_stack *b)
{
	int	max_index;

	while (b->size > 0)
	{
		max_index = get_max_index(b);
		move_max_to_top(b, max_index);
		pa(a, b);
	}
}

void	sort_big(t_stack *a, t_stack *b)
{
	int	chunk_count;

	chunk_count = get_chunk_count(a->size);
	push_chunks(a, b, chunk_count);
	push_back_sorted(a, b);
}
