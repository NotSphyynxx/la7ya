/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sphynx <sphynx@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:54:43 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/04/27 16:08:18 by sphynx           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_countword(char *str, char c)
{
	size_t	i;
	int		wc;
	size_t	wz;

	i = 0;
	wc = 0;
	wz = 1;
	while (str[i])
	{
		if (wz == 1 && str[i] != c)
		{
			wc++;
			wz = 0;
		}
		if (str[i] == c)
			wz = 1;
		i++;
	}
	return (wc);
}

static int	ft_strlentillsep(char *str, char set)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != set)
		i++;
	return (i);
}

static char	*ft_allocword(char *str, char set)
{
	int		len;
	int		i;
	char	*word;

	i = 0;
	len = ft_strlentillsep(str, set);
	word = (char *)malloc((len + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**skip_and_free(const char *s, char **motherstrings, char c, int mi)
{
	int	si;

	si = 0;
	while (s[si])
	{
		while (s[si] && s[si] == c)
			si++;
		if (s[si])
		{
			motherstrings[mi] = ft_allocword((char *)(s + si), c);
			if (motherstrings[mi] == NULL)
			{
				while (--mi >= 0)
					free(motherstrings[mi]);
				free(motherstrings);
				return (NULL);
			}
			mi++;
		}
		while (s[si] && s[si] != c)
			si++;
	}
	motherstrings[mi] = NULL;
	return (motherstrings);
}

char	**ft_split(char const *s, char c)
{
	int		mi;
	size_t	wc;
	char	**motherstrings;

	if (!s)
		return (NULL);
	mi = 0;
	wc = (size_t)ft_countword((char *)s, c);
	motherstrings = (char **)malloc((wc + 1) * sizeof(char *));
	if (motherstrings == NULL)
		return (NULL);
	motherstrings = skip_and_free(s, motherstrings, c, mi);
	return (motherstrings);
}
