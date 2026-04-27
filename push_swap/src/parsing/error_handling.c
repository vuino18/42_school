/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 09:36:41 by elino             #+#    #+#             */
/*   Updated: 2025/11/17 11:36:15 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	has_duplicates(int *numbers, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (numbers[i] == numbers[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	fill_from_arg(char *arg, int *numbers, int *count)
{
	char	**split;
	long	num;
	int		j;
	int		is_valid;

	if (is_empty_or_spaces(arg))
		return (-1);
	split = ft_split(arg, ' ');
	if (!split)
		return (-1);
	j = 0;
	while (split[j])
	{
		num = ft_atoi_safe(split[j], &is_valid);
		if (!is_valid || num < INT_MIN || num > INT_MAX)
			return (free_split(split), -1);
		numbers[*count] = (int)num;
		(*count)++;
		j++;
	}
	free_split(split);
	return (0);
}

static int	fill_numbers(char **argv, int argc, int *numbers)
{
	int	i;
	int	count;
	int	result;

	count = 0;
	i = 1;
	while (i < argc)
	{
		result = fill_from_arg(argv[i], numbers, &count);
		if (result == -1)
			return (-1);
		i++;
	}
	return (count);
}

static int	count_numbers(char **argv, int argc)
{
	char	**split;
	int		i;
	int		j;
	int		count;

	i = 1;
	count = 0;
	while (i < argc)
	{
		if (is_empty_or_spaces(argv[i]))
			return (-1);
		split = ft_split(argv[i], ' ');
		if (!split)
			return (-1);
		j = 0;
		while (split[j])
			j++;
		count += j;
		free_split(split);
		i++;
	}
	return (count);
}

int	check_errors(int argc, char **argv)
{
	int	*numbers;
	int	count;	

	if (argc < 2)
		return (0);
	count = count_numbers(argv, argc);
	if (count <= 0)
		return (write(2, "Error\n", 6), 1);
	numbers = malloc(sizeof(int) * count);
	if (!numbers)
		return (write(2, "Error\n", 6), 1);
	count = fill_numbers(argv, argc, numbers);
	if (count == -1 || has_duplicates(numbers, count))
		return (free(numbers), write(2, "Error\n", 6), 1);
	free(numbers);
	return (0);
}
