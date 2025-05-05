/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstadd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:38:21 by bael-bad          #+#    #+#             */
/*   Updated: 2025/05/05 17:16:23 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*crnt;

	if (new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		crnt = *lst;
		while (crnt->next != NULL)
		{
			crnt = crnt->next;
		}
		crnt->next = new;
	}
}
