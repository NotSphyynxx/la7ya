/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:13:25 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/04/23 17:34:53 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int shell_echo(char **av)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if (av[1] && av[1][0] == '-' && av[1][1] == 'n' && av[1][2] == '\0')
	{
		new_line = 0;
		i = 2;
	}
	while (av[i])
	{
		while (*av[i])
		{
			write (STDOUT_FILENO, av[i], 1);
			av[i]++;
		}
		if (av[i + 1])
			write (STDOUT_FILENO, " ", 1);
		i++;
	}
	if (new_line)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}



int main(int ac, char **av)
{
	if (ac > 1)
	{
		av++;
		shell_echo(av);
	}
}