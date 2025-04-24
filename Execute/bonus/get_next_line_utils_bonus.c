/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 09:45:42 by ildaboun          #+#    #+#             */
/*   Updated: 2025/02/27 23:26:56 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

size_t	ft_strlenn(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
