/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extension_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:00:03 by elino             #+#    #+#             */
/*   Updated: 2025/12/04 17:00:19 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_extension(char *file, t_game *game)
{
	int	len;

	len = ft_strlen(file);
	if (len < 4)
		error_exit("Invalid file extension", game);
	if (file[0] == '.')
		error_exit("Invalid map filename", game);
	if (file[len - 4] != '.' || file[len - 3] != 'b'
		|| file[len - 2] != 'e' || file[len - 1] != 'r')
		error_exit("File must have .ber extension", game);
}
