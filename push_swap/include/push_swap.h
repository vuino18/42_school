/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:21:51 by elino             #+#    #+#             */
/*   Updated: 2025/10/30 14:33:32 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_node
{
	struct s_node	*next;
	struct s_node	*prev;
	int				value;
	int				index;
}	t_node;

typedef struct s_stack
{
	t_node	*top;
	t_node	*bottom;
	int		size;
}	t_stack;

void	sa(t_stack *a);
void	sb(t_stack *b);
void	ss(t_stack *a, t_stack *b);
void	ra(t_stack *a);
void	rb(t_stack *b);
void	rr(t_stack *a, t_stack *b);
void	rra(t_stack *a);
void	rrb(t_stack *b);
void	rrr(t_stack *a, t_stack *b);
void	pa(t_stack *a, t_stack *b);
void	pb(t_stack *a, t_stack *b);
void	sort_two(t_stack *a);
void	sort_three(t_stack *a);
void	sort_five(t_stack *a, t_stack *b);
void	sort_big(t_stack *a, t_stack *b);
void	free_split(char **split);
t_stack	*stack_init(int argc, char **argv);
t_stack	*init_empty_stack(void);
void	push_value(t_stack *stack, int value);
void	free_stack(t_stack *stack);
int		is_sorted(t_stack *stack);
int		get_min(t_stack *a);
int		get_index(t_stack *a, int value);
int		is_empty_or_spaces(char *s);
void	move_min_to_top(t_stack *a);
long	ft_atoi_safe(const char *str, int *is_valid);
int		get_max(t_stack *a);
int		has_duplicates(int *numbers, int size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
int		check_errors(int argc, char **argv);
int		get_max_index(t_stack *a);
void	assign_indexes(t_stack *stack);
void	move_max_to_top(t_stack *a, int max_index);
char	**ft_split(char const *s, char c);

#endif
