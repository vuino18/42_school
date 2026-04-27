/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:46:32 by elino             #+#    #+#             */
/*   Updated: 2025/09/04 14:46:18 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char *buffer)
{
	size_t	i;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_substr(buffer, 0, i);
	return (line);
}

static char	*cut_buffer(char *buffer)
{
	size_t	i;
	char	*new_buffer;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	new_buffer = ft_strdup(buffer + i);
	free(buffer);
	return (new_buffer);
}

static char	*append_until_newline(int fd, char *buffer, char *temp)
{
	ssize_t	bytes_read;
	char	*joined;

	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		temp[bytes_read] = '\0';
		joined = ft_strjoin(buffer, temp);
		free(buffer);
		if (!joined)
			return (NULL);
		buffer = joined;
	}
	return (buffer);
}

static char	*read_and_append(int fd, char *buffer)
{
	char	*temp;

	temp = (char *)malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	if (!buffer)
		buffer = ft_strdup("");
	if (!buffer)
	{
		free(temp);
		return (NULL);
	}
	buffer = append_until_newline(fd, buffer, temp);
	free(temp);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_and_append(fd, buffer);
	if (!buffer || !*buffer)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = extract_line(buffer);
	buffer = cut_buffer(buffer);
	return (line);
}
