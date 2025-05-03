/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:56:29 by bael-bad          #+#    #+#             */
/*   Updated: 2025/04/19 11:57:12 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	ft_strlcpy(char *dst, char *src, int dstsize)
{
	int	i;
	int	len;

	len = ft_strlen(src);
	if (dstsize == 0)
		return (len);
	i = 0;
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}

static int	count_ws(char *s, char c)
{
	int	i;
	int	count;
	int	word;

	i = 0;
	word = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			word = 0;
		else if (word == 0)
		{
			word = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static int	lenstr(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] && s[i] != c)
	{
		count++;
		i++;
	}
	return (count);
}

static char	**freemem(char **s, int i)
{
	int	index;

	index = 0;
	while (index < i)
	{
		free(s[index]);
		index++;
	}
	free(s);
	return (NULL);
}

char	**ft_split(char *s, char c)
{
	char	**ptr;
	int		len;
	int		index;

	if (!s)
		return (NULL);
	len = count_ws(s, c);
	ptr = malloc((len + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	index = 0;
	while (index < len)
	{
		while (*s == c)
			s++;
		ptr[index] = malloc((lenstr(s, c) + 1) * sizeof(char));
		if (!ptr[index])
			return (freemem(ptr, index));
		ft_strlcpy(ptr[index], s, (lenstr(s, c) + 1));
		s = s + lenstr(s, c);
		index++;
	}
	ptr[index] = NULL;
	return (ptr);
}
