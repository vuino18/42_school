/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 17:55:57 by elino             #+#    #+#             */
/*   Updated: 2025/11/22 18:02:26 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(char *msg)
{
	perror(msg);
	exit(1);
}

void	close_all(int *p)
{
	close(p[0]);
	close(p[1]);
}

char	*join_three(char *a, char *b, char *c)
{
	char	*ab;
	char	*abc;

	ab = ft_strjoin(a, b);
	if (!ab)
		return (NULL);
	abc = ft_strjoin(ab, c);
	free(ab);
	return (abc);
}
