/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 23:13:06 by ildaboun          #+#    #+#             */
/*   Updated: 2025/02/18 16:45:58 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((unsigned char) *str1 && (unsigned char) *str2 && i < n)
	{
		if ((unsigned char) *str1 != (unsigned char) *str2)
			return ((unsigned char) *str1 - (unsigned char) *str2);
		str1++;
		str2++;
		i++;
	}
	if (i < n)
		return ((unsigned char) *str1 - (unsigned char) *str2);
	return (0);
}
