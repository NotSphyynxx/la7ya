/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:37:47 by ildaboun          #+#    #+#             */
/*   Updated: 2025/03/07 04:38:05 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*arr;
	unsigned char	*err;

	if (dst == src)
		return (dst);
	if (dst == (void *) 0 && src == (void *) 0)
		return (dst);
	arr = (unsigned char *) dst;
	err = (unsigned char *) src;
	i = 0;
	while (i < n)
	{
		arr[i] = err[i];
		i++;
	}
	return (dst);
}

void	free_fd(int **fd, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}

int	**allocate_fd(int rows)
{
	int	**fd;
	int	i;

	i = 0;
	fd = malloc(rows * sizeof(int *));
	if (!fd)
		return (NULL);
	while (i < rows)
	{
		fd[i] = malloc(2 * sizeof(int));
		if (!fd[i])
			return (NULL);
		i++;
	}
	return (fd);
}

void	last_step(char **argv, t_info *info, int **fd)
{
	if (info->outfile == -1)
		info->outfile = open_file(argv[info->lst_argm - 1], 2, info);
	if (dup2(info->outfile, STDOUT_FILENO) == -1)
	{
		close(info->outfile);
		close(info->infile);
		pipe_free(info, fd);
		handle_dup();
	}
	close(info->outfile);
}
