/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:37:47 by ildaboun          #+#    #+#             */
/*   Updated: 2025/03/04 22:12:27 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

char	*ft_strdup(const char *s1)
{
	int		len_src;
	char	*copy;
	char	*save;

	len_src = ft_strlen(s1);
	copy = (char *) malloc(sizeof(char) * (len_src + 1));
	if (copy == NULL)
		return (NULL);
	save = copy;
	while (*s1)
		*copy++ = *s1++;
	*copy = '\0';
	return (save);
}

void	fork_fail(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
	write(2, "bash: fork: Resource temporarily unavailable", 45);
	exit(1);
}

void	pipe_fail(void)
{
	write(2, "bash: pipe: Resource temporarily unavailable", 45);
	exit(1);
}
