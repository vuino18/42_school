/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:14:21 by elino             #+#    #+#             */
/*   Updated: 2025/12/04 16:17:21 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_valid_char(char c)
{
	if (c == '0' || c == '1' || c == 'C' || c == 'E' || c == 'P')
		return (1);
	return (0);
}

void	validate_characters(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (!is_valid_char(game->map.grid[i][j]))
				error_exit("Invalid character in map", game);
			j++;
		}
		i++;
	}
}

void	check_rectangular(t_game *game)
{
	int	i;
	int	len;

	i = 0;
	while (i < game->map.height)
	{
		len = ft_strlen(game->map.grid[i]);
		if (len != game->map.width)
			error_exit("Map must be rectangular", game);
		i++;
	}
}

void	check_walls(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		if (game->map.grid[i][0] != '1'
			|| game->map.grid[i][game->map.width - 1] != '1')
			error_exit("Map must be surrounded by walls", game);
		i++;
	}
	j = 0;
	while (j < game->map.width)
	{
		if (game->map.grid[0][j] != '1'
			|| game->map.grid[game->map.height - 1][j] != '1')
			error_exit("Map must be surrounded by walls", game);
		j++;
	}
}

void	cleanup_map_parsing(t_game *game)
{
	int	i;

	if (!game->map.grid)
		return ;
	i = 0;
	while (i < game->map.height)
	{
		if (game->map.grid[i])
			free(game->map.grid[i]);
		i++;
	}
	free(game->map.grid);
	game->map.grid = NULL;
}
