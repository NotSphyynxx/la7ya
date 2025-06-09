/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 15:00:29 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/08 16:19:14 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strnstr(const char *hs, const char *n, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	nlen;

	nlen = ft_strlen(n);
	if (!hs && len == 0)
		return (NULL);
	if (nlen == 0)
		return ((char *)hs);
	if (len == 0)
		return (NULL);
	i = 0;
	while (hs[i] != '\0' && i + nlen <= len)
	{
		j = 0;
		while (j < nlen && hs[i + j] == n[j] && (i + j) < len)
			j++;
		if (j == nlen)
			return ((char *)(hs + i));
		i++;
	}
	return (NULL);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (fd < 0)
		return ;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	i;

	src_len = 0;
	while (src[src_len])
		src_len++;
	if (dstsize == 0)
		return (src_len);
	i = 0;
	while ((i < (dstsize - 1)) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dl;
	size_t	sl;
	size_t	i;

	i = 0;
	sl = 0;
	dl = 0;
	if (!dst && !dstsize)
		return (ft_strlen(src));
	while (dst[dl] && dl < dstsize)
		dl++;
	while (src[sl])
		sl++;
	if (dl >= dstsize)
		return (dstsize + sl);
	while (src[i] && ((dl + i) < dstsize - 1))
	{
		dst[dl + i] = src[i];
		i++;
	}
	dst[dl + i] = '\0';
	return (dl + sl);
}
