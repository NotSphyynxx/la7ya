/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 23:10:12 by ildaboun          #+#    #+#             */
/*   Updated: 2025/03/04 21:56:37 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	malloc_fd_fail(t_info *info)
{
	close(info->infile);
	close(info->outfile);
	write(2, "bash: pipe: Resource temporarily unavailable", 45);
	exit(1);
}
