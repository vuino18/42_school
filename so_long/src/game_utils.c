/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 10:01:08 by elino             #+#    #+#             */
/*   Updated: 2025/11/30 10:01:36 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_moves(t_game *game)
{
	ft_putstr_fd("Moves: ", 1);
	ft_putnbr_fd(game->moves, 1);
	ft_putstr_fd("\n", 1);
}

void	check_win(t_game *game)
{
	if (game->map.collected == game->map.collectibles
		&& game->map.grid[game->map.player_pos.y]
		[game->map.player_pos.x] == 'E')
	{
		ft_putstr_fd("You win!\n", 1);
		close_window(game);
	}
}

int	close_window(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}
