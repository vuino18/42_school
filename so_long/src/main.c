/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 09:32:18 by elino             #+#    #+#             */
/*   Updated: 2025/11/30 09:32:48 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_game(t_game *game, char *file)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		error_exit("Failed to initialize MLX", NULL);
	game->moves = 0;
	game->map.collected = 0;
	game->map.grid = NULL;
	game->img.wall = NULL;
	game->img.floor = NULL;
	game->img.collect = NULL;
	game->img.exit = NULL;
	game->img.player = NULL;
	game->win = NULL;
	parse_map(game, file);
	validate_map(game);
	check_path(game);
	load_images(game);
	game->win = mlx_new_window(game->mlx, game->map.width * TILE_SIZE,
			game->map.height * TILE_SIZE, "so_long");
	if (!game->win)
		error_exit("Failed to create window", game);
}

void	run_game(t_game *game)
{
	render_map(game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_loop(game->mlx);
}

void	cleanup_game(t_game *game)
{
	if (!game || !game->mlx)
		return ;
	if (game->img.wall)
		mlx_destroy_image(game->mlx, game->img.wall);
	if (game->img.floor)
		mlx_destroy_image(game->mlx, game->img.floor);
	if (game->img.collect)
		mlx_destroy_image(game->mlx, game->img.collect);
	if (game->img.exit)
		mlx_destroy_image(game->mlx, game->img.exit);
	if (game->img.player)
		mlx_destroy_image(game->mlx, game->img.player);
	if (game->map.grid)
		free_grid(game->map.grid);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	game->mlx = NULL;
}

void	error_exit(char *msg, t_game *game)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	if (game)
	{
		cleanup_map_parsing(game);
		if (game->mlx)
			cleanup_game(game);
	}	
	exit(1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		error_exit("Usage: ./so_long map.ber", NULL);
	init_game(&game, argv[1]);
	run_game(&game);
	return (0);
}
