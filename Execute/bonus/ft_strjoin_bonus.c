/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:25:15 by ildaboun          #+#    #+#             */
/*   Updated: 2025/03/01 19:57:50 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		len_s1;
	int		len_s2;
	int		totale;
	char	*arr;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	if (!*s1 && !*s2)
		return (ft_strdup(""));
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	totale = len_s1 + len_s2;
	arr = (char *) malloc(sizeof(char) * (totale + 1));
	if (arr == NULL)
		return (NULL);
	ft_memcpy(arr, s1, len_s1);
	ft_memcpy(arr + len_s1, s2, len_s2 + 1);
	return (arr);
}
