/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:38:55 by ildaboun          #+#    #+#             */
/*   Updated: 2025/02/18 16:12:57 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	strleen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

static char	*get_word(const char *s, char c)
{
	int		i;
	char	*arr;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	arr = (char *)malloc(sizeof(char) * (i + 1));
	if (arr == NULL)
		return (NULL);
	ft_memcpy(arr, s, i);
	arr[i] = '\0';
	return (arr);
}

static int	count_words(const char *str, char c)
{
	int	i;
	int	count;
	int	check;

	i = 0;
	count = 0;
	check = 1;
	while (str[i])
	{
		if (str[i] == c)
		{
			check = 1;
		}
		else
		{
			if (check == 1)
			{
				count++;
				check = 0;
			}
		}
		i++;
	}
	return (count);
}

static void	free_fail(char **arr, int size)
{
	while (size-- > 0)
		free(arr[size]);
	free(arr);
}

char	**ft_split(const char *s, char c)
{
	char	**arr;
	int		i;
	int		many_word;

	if (s == NULL)
		return (NULL);
	i = 0;
	many_word = count_words(s, c);
	arr = (char **)malloc(sizeof(char *) * (many_word + 1));
	if (arr == NULL)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			arr[i] = get_word(s, c);
			if (arr[i++] == NULL)
				return (free_fail(arr, i), NULL);
			s += strleen(arr[i - 1]);
		}
		else
			s++;
	}
	arr[i] = NULL;
	return (arr);
}
