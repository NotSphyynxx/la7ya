/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper_7.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:22:54 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/05/22 15:25:33 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wait_for_children(void)
{
	while (wait(NULL) > 0)
		;
}

int	has_equal_sign(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	is_append_export(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i] == '+' && av[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}
