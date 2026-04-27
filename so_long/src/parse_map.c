/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 09:36:01 by elino             #+#    #+#             */
/*   Updated: 2025/11/30 09:36:07 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	open_map_file(char *file, t_game *game)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open map file", game);
	return (fd);
}

static void	validate_map_dimensions(t_game *game, int row)
{
	if (row == 0)
		game->map.width = ft_strlen(game->map.grid[0]);
	if ((int)ft_strlen(game->map.grid[row]) != game->map.width)
		error_exit("Inconsistent map width", game);
}

int	parse_map(t_game *game, char *file)
{
	int		fd;
	char	*line;
	int		row;

	check_extension(file, game);
	init_map_data(game);
	game->map.height = count_lines(file, game);
	game->map.grid = allocate_grid(game->map.height);
	fd = open_map_file(file, game);
	row = 0;
	line = get_next_line(fd);
	while (line)
	{
		read_map_line(game, line, row);
		validate_map_dimensions(game, row);
		free(line);
		line = get_next_line(fd);
		row++;
	}
	close(fd);
	return (1);
}
