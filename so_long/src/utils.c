/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 09:35:12 by elino             #+#    #+#             */
/*   Updated: 2025/11/30 09:35:13 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_grid(char **grid)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

int	count_lines(char *file, t_game *game)
{
	int		fd;
	int		lines;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open map file", game);
	lines = 0;
	line = get_next_line(fd);
	while (line)
	{
		lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (lines == 0)
		error_exit("Map file is empty", game);
	return (lines);
}

char	**allocate_grid(int lines)
{
	char	**grid;
	int		i;

	grid = malloc(sizeof(char *) * (lines + 1));
	if (!grid)
		return (NULL);
	i = 0;
	while (i < lines)
	{
		grid[i] = NULL;
		i++;
	}
	grid[lines] = NULL;
	return (grid);
}
