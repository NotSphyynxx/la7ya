/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 09:45:02 by ildaboun          #+#    #+#             */
/*   Updated: 2025/02/26 17:00:13 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*extract(char **lefty)
{
	char	*line;
	char	*check;
	char	*save;

	if (!*lefty || **lefty == '\0')
		return (NULL);
	check = ft_strchr(*lefty, '\n');
	if (check)
	{
		line = ft_substr(*lefty, 0, (check - *lefty) + 1);
		if (!line)
			return (free(*lefty), *lefty = NULL, NULL);
		save = ft_strdup(check + 1);
		if (!save)
			return (free(*lefty), free(line), *lefty = NULL, NULL);
		return (free(*lefty), *lefty = save, line);
	}
	else
	{
		line = ft_strdup(*lefty);
		if (!line)
			return (free(*lefty), *lefty = NULL, NULL);
		return (free(*lefty), *lefty = NULL, line);
	}
}

static char	*appand(char **leftover, char **buffer)
{
	char	*save;

	if (!*buffer)
		return (NULL);
	if (!*leftover)
	{
		*leftover = ft_strdup(*buffer);
		if (!*leftover)
			return (free(*buffer), NULL);
	}
	else
	{
		save = ft_strjoin(*leftover, *buffer);
		if (!save)
			return (free(*buffer), free(*leftover), *leftover = NULL, NULL);
		free(*leftover);
		*leftover = save;
	}
	return (*leftover);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*leftover[10240];
	ssize_t		i;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 10240 || BUFFER_SIZE > 2147483647)
		return (NULL);
	buffer = malloc(((size_t)BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	i = read(fd, buffer, ((size_t)BUFFER_SIZE));
	while (i > 0)
	{
		buffer[i] = '\0';
		leftover[fd] = appand(&leftover[fd], &buffer);
		if (!leftover[fd])
			return (NULL);
		if (ft_strchr(leftover[fd], '\n'))
			break ;
		i = read(fd, buffer, BUFFER_SIZE);
	}
	if (i < 0 || !leftover[fd] || (*leftover[fd] == '\0' && i == 0))
		return (free(buffer), free(leftover[fd]), leftover[fd] = NULL, NULL);
	free(buffer);
	return (extract(&leftover[fd]));
}
