/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:20:48 by bael-bad          #+#    #+#             */
/*   Updated: 2025/05/05 17:16:17 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*ft_strdup(char *s1)
{
	char	*tmp;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s1);
	tmp = malloc((len + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	while (s1[i])
	{
		tmp[i] = s1[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
