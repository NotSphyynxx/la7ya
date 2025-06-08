/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 15:00:36 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/08 15:00:37 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(const char *s, int c)
{
	char	ch;
	size_t	i;

	i = 0;
	ch = (char)c;
	while (s[i])
	{
		if (s[i] == ch)
			return ((char *)&s[i]);
		i++;
	}
	if (ch == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

static char	*allocate_substring(size_t len)
{
	char	*substring;

	substring = (char *)malloc(len * sizeof(char) + 1);
	if (!substring)
		return (NULL);
	substring[len] = '\0';
	return (substring);
}

char	*ft_substr(char const *novel, unsigned int start, size_t len)
{
	size_t	novel_len;
	char	*book;
	size_t	i;

	novel_len = ft_strlen(novel);
	if (start >= novel_len)
		return (allocate_substring(0));
	if (len > novel_len - start)
		len = novel_len - start;
	book = allocate_substring(len);
	if (!book)
		return (NULL);
	i = 0;
	while (i < len && novel[start + i])
	{
		book[i] = novel[start + i];
		i++;
	}
	book[i] = '\0';
	return (book);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*d;

	d = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (d == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		d[i] = s1[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

int	ft_isalnum(int ch)
{
	if ((ch >= 'a' && ch <= 'z')
		|| (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'))
		return (1);
	return (0);
}
