/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 23:03:13 by bael-bad          #+#    #+#             */
/*   Updated: 2025/05/04 23:03:32 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;
	char	char_c;

	str = (char *)s;
	char_c = (char)c;
	i = 0;
	if (!char_c)
		return (str + ft_strlen(str));
	while (s[i])
	{
		if (s[i] == char_c)
			return (str + i);
		i++;
	}
	return (NULL);
}
