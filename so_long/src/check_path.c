/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 09:58:04 by elino             #+#    #+#             */
/*   Updated: 2025/11/30 09:58:07 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_partial_copy(char **copy, int lines)
{
	while (lines > 0)
		free(copy[--lines]);
	free(copy);
}

static char	*copy_line(char *line, t_game *game, char **copy, int i)
{
	char	*new_line;
	int		j;
	int		len;

	len = ft_strlen(line);
	new_line = malloc(sizeof(char) * (len + 1));
	if (!new_line)
	{
		free_partial_copy(copy, i);
		error_exit("Memory allocation failed", game);
	}
	j = 0;
	while (j < len)
	{
		new_line[j] = line[j];
		j++;
	}
	new_line[j] = '\0';
	return (new_line);
}

static char	**copy_map(t_game *game)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (game->map.height + 1));
	if (!copy)
		error_exit("Memory allocation failed", game);
	i = 0;
	while (i < game->map.height)
	{
		copy[i] = copy_line(game->map.grid[i], game, copy, i);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	flood_fill(t_flood *flood, int x, int y)
{
	if (y < 0 || x < 0 || y >= flood->height || x >= flood->width)
		return ;
	if (flood->map[y][x] == '1' || flood->map[y][x] == 'V')
		return ;
	if (flood->map[y][x] == 'E')
	{
		flood->found[1] = 1;
		return ;
	}
	if (flood->map[y][x] == 'C')
		flood->found[0]++;
	flood->map[y][x] = 'V';
	flood_fill(flood, x + 1, y);
	flood_fill(flood, x - 1, y);
	flood_fill(flood, x, y + 1);
	flood_fill(flood, x, y - 1);
}

void	check_path(t_game *game)
{
	t_flood	flood;
	int		found[2];

	if (!game->map.grid || game->map.height <= 0)
		error_exit("Invalid map data", game);
	found[0] = 0;
	found[1] = 0;
	flood.map = copy_map(game);
	flood.width = game->map.width;
	flood.height = game->map.height;
	flood.found = found;
	flood_fill(&flood, game->map.player_pos.x, game->map.player_pos.y);
	free_grid(flood.map);
	if (found[0] != game->map.collectibles)
		error_exit("Not all collectibles are reachable", game);
	if (found[1] != 1)
		error_exit("Exit is not reachable", game);
}
