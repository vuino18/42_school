/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 14:34:31 by elino             #+#    #+#             */
/*   Updated: 2025/10/31 12:11:53 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	handle_sorting(t_stack *a, t_stack *b)
{
	if (is_sorted(a))
		return ;
	if (a->size == 2)
		sort_two(a);
	else if (a->size == 3)
		sort_three(a);
	else if (a->size <= 5)
		sort_five(a, b);
	else
		sort_big(a, b);
}

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	if (check_errors(argc, argv))
		return (1);
	if (argc < 2)
		return (0);
	a = stack_init(argc, argv);
	if (!a)
		return (1);
	b = init_empty_stack();
	if (!b)
		return (free_stack(a), 1);
	handle_sorting(a, b);
	free_stack(a);
	free_stack(b);
	return (0);
}
