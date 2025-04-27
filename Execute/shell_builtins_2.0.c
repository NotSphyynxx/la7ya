/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_builtins_2.0.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sphynx <sphynx@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:07:24 by sphynx            #+#    #+#             */
/*   Updated: 2025/04/27 18:11:07 by sphynx           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int shell_export(char **av, char **envp)
{
	char	**env;
	char	**name;
	char	**value;
	int		i;

	i = 1;
	if (av[1])
	{
		env = *envp;
		while (*env)
		{
			write(STDOUT_FILENO, *env, ft_strlen(*env));
			write (STDOUT_FILENO, "\n", 1);
			env++;
		}
		return (0);
	}
	
}