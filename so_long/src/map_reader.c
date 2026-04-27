/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:58:47 by elino             #+#    #+#             */
/*   Updated: 2025/12/04 16:59:19 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	process_char(t_game *game, char c, int x, int y)
{
	if (c == 'P')
	{
		game->map.players++;
		game->map.player_pos.x = x;
		game->map.player_pos.y = y;
	}
	else if (c == 'C')
		game->map.collectibles++;
	else if (c == 'E')
	{
		game->map.exits++;
		game->map.exit_pos.x = x;
		game->map.exit_pos.y = y;
	}
	else if (c != '0' && c != '1')
		error_exit("Invalid character in map", game);
}

void	read_map_line(t_game *game, char *line, int row)
{
	int	col;
	int	len;

	len = ft_strlen(line);
	if (len == 0 || (len == 1 && line[0] == '\n'))
		error_exit("Empty line in map", game);
	if (line[len - 1] == '\n')
		len--;
	game->map.grid[row] = malloc(sizeof(char) * (len + 1));
	if (!game->map.grid[row])
		error_exit("Memory allocation failed", game);
	col = 0;
	while (col < len)
	{
		process_char(game, line[col], col, row);
		game->map.grid[row][col] = line[col];
		col++;
	}
	game->map.grid[row][col] = '\0';
}
