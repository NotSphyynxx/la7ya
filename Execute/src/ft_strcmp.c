/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 23:10:12 by ildaboun          #+#    #+#             */
/*   Updated: 2025/03/06 17:40:00 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char	*ft_strchr(const char *str, int c)
{
	char	d;

	d = (char) c;
	while (*str)
	{
		if (*str == d)
			return ((char *)(str));
		str++;
	}
	if (*str == d)
		return ((char *)(str));
	return (NULL);
}
