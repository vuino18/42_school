/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 18:18:57 by elino             #+#    #+#             */
/*   Updated: 2025/12/04 18:19:07 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"
# include "get_next_line.h"

# define TILE_SIZE 64

# ifdef __APPLE__
#  define KEY_ESC 53
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
# else
#  define KEY_ESC 65307
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
# endif

typedef struct s_flood
{
	char	**map;
	int		width;
	int		height;
	int		*found;
}	t_flood;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_img
{
	void	*wall;
	void	*floor;
	void	*collect;
	void	*exit;
	void	*player;
}	t_img;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		collectibles;
	int		collected;
	int		exits;
	int		players;
	t_point	player_pos;
	t_point	exit_pos;
}	t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_map	map;
	t_img	img;
	int		moves;
}	t_game;

int		main(int argc, char **argv);
void	init_game(t_game *game, char *file);
void	init_map_data(t_game *game);
void	run_game(t_game *game);
void	cleanup_game(t_game *game);
void	cleanup_map_parsing(t_game *game);
void	error_exit(char *msg, t_game *game);

int		parse_map(t_game *game, char *file);
void	validate_map(t_game *game);
void	read_map_line(t_game *game, char *line, int row);
void	validate_characters(t_game *game);
void	check_rectangular(t_game *game);
void	check_extension(char *file, t_game *game);
void	check_walls(t_game *game);
void	check_path(t_game *game);

void	load_images(t_game *game);
void	render_map(t_game *game);
void	put_image(t_game *game, void *img, int x, int y);

int		key_press(int keycode, t_game *game);
void	move_player(t_game *game, int dx, int dy);
void	update_position(t_game *game, int new_x, int new_y, char target);
int		close_window(t_game *game);
void	print_moves(t_game *game);
void	check_win(t_game *game);

void	free_grid(char **grid);
int		count_lines(char *file, t_game *game);
char	**allocate_grid(int lines);
void	flood_fill(t_flood *flood, int x, int y);

#endif
