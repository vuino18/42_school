/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 09:35:32 by elino             #+#    #+#             */
/*   Updated: 2025/11/30 09:35:37 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_images(t_game *game)
{
	int	w;
	int	h;

	w = TILE_SIZE;
	h = TILE_SIZE;
	game->img.wall = mlx_xpm_file_to_image(game->mlx,
			"textures/wall.xpm", &w, &h);
	if (!game->img.wall)
		error_exit("Failed to load wall.xpm", game);
	game->img.floor = mlx_xpm_file_to_image(game->mlx,
			"textures/floor.xpm", &w, &h);
	if (!game->img.floor)
		error_exit("Failed to load floor.xpm", game);
	game->img.collect = mlx_xpm_file_to_image(game->mlx,
			"textures/collectible.xpm", &w, &h);
	if (!game->img.collect)
		error_exit("Failed to load collectible.xpm", game);
	game->img.exit = mlx_xpm_file_to_image(game->mlx,
			"textures/exit.xpm", &w, &h);
	if (!game->img.exit)
		error_exit("Failed to load exit.xpm", game);
	game->img.player = mlx_xpm_file_to_image(game->mlx,
			"textures/player.xpm", &w, &h);
	if (!game->img.player)
		error_exit("Failed to load player.xpm", game);
}

void	put_image(t_game *game, void *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, img,
		x * TILE_SIZE, y * TILE_SIZE);
}

static void	render_tile(t_game *game, int x, int y)
{
	char	tile;

	tile = game->map.grid[y][x];
	put_image(game, game->img.floor, x, y);
	if (tile == '1')
		put_image(game, game->img.wall, x, y);
	else if (tile == 'C')
		put_image(game, game->img.collect, x, y);
	else if (tile == 'E')
	{
		put_image(game, game->img.exit, x, y);
		if (x == game->map.player_pos.x && y == game->map.player_pos.y)
			put_image(game, game->img.player, x, y);
	}
	else if (tile == 'P')
		put_image(game, game->img.player, x, y);
}

void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			render_tile(game, x, y);
			x++;
		}
		y++;
	}
}
