/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 09:37:07 by elino             #+#    #+#             */
/*   Updated: 2025/12/04 16:23:20 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_screen_size(t_game *game)
{
	int	screen_width;
	int	screen_height;
	int	map_width;
	int	map_height;

	screen_width = 1920;
	screen_height = 1080;
	map_width = game->map.width * TILE_SIZE;
	map_height = game->map.height * TILE_SIZE;
	if (map_width > screen_width || map_height > screen_height)
		error_exit("Map is too large for screen", game);
}

void	validate_map(t_game *game)
{
	if (game->map.players != 1)
		error_exit("Map must have exactly one player", game);
	if (game->map.exits != 1)
		error_exit("Map must have exactly one exit", game);
	if (game->map.collectibles < 1)
		error_exit("Map must have at least one collectible", game);
	validate_characters(game);
	check_rectangular(game);
	check_walls(game);
	check_screen_size(game);
}
