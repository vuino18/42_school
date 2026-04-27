/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:57:46 by elino             #+#    #+#             */
/*   Updated: 2025/12/04 16:58:11 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_map_data(t_game *game)
{
	game->map.collectibles = 0;
	game->map.exits = 0;
	game->map.players = 0;
	game->map.width = 0;
	game->map.height = 0;
}
