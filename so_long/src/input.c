/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 09:57:53 by elino             #+#    #+#             */
/*   Updated: 2025/11/30 09:57:56 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_window(game);
	else if (keycode == KEY_W)
		move_player(game, 0, -1);
	else if (keycode == KEY_S)
		move_player(game, 0, 1);
	else if (keycode == KEY_A)
		move_player(game, -1, 0);
	else if (keycode == KEY_D)
		move_player(game, 1, 0);
	return (0);
}

void	update_position(t_game *game, int new_x, int new_y, char target)
{
	char	current;

	current = game->map.grid[game->map.player_pos.y][game->map.player_pos.x];
	if (current == 'P')
		game->map.grid[game->map.player_pos.y][game->map.player_pos.x] = '0';
	game->map.player_pos.x = new_x;
	game->map.player_pos.y = new_y;
	if (target != 'E')
		game->map.grid[new_y][new_x] = 'P';
	else
		game->map.grid[new_y][new_x] = 'E';
}

void	move_player(t_game *game, int dx, int dy)
{
	int		new_x;
	int		new_y;
	char	target;

	new_x = game->map.player_pos.x + dx;
	new_y = game->map.player_pos.y + dy;
	target = game->map.grid[new_y][new_x];
	if (target == '1')
		return ;
	if (target == 'E' && game->map.collected != game->map.collectibles)
		return ;
	if (target == 'C')
		game->map.collected++;
	update_position(game, new_x, new_y, target);
	game->moves++;
	print_moves(game);
	render_map(game);
	check_win(game);
}
