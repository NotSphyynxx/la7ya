/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_builtins_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:53:37 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/05/21 17:13:19 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void search_then_unset(char **env, char *name)
{
	int i = 0;
	int j;
	int len = ft_strlen(name);

	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
		{
			free(env[i]);
			j = i;
			while (env[j + 1])
			{
				env[j] = env[j + 1];
				j++;
			}
			env[j] = NULL;
			return ;
		}
		i++;
	}
}

int shell_unset(char **av)
{
	char **env;
	int i = 1;

	env = *get_env();
	while (av[i])
	{
		if (ft_strchr(av[i], '=') != NULL)
		{
			write(STDERR_FILENO, "unset: not a valid identifier\n", 31);
			return (1);
		}
		search_then_unset(env, av[i]);
		i++;
	}
	return (0);
}
 
static int	is_valid_number(char *str)
{
	int i = 0;

	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int shell_exit(char **av)
{
	int exit_code;

	write(STDOUT_FILENO, "exit\n", 5);
	if (!av[1])
		exit(0);
	
	if (!is_valid_number(av[1]))
	{
		write(STDERR_FILENO, "exit: numeric argument required\n", 32);
		exit(255);
	}
	exit_code = ft_atoi(av[1]);
	if (av[2])
	{
		write(STDERR_FILENO, "exit: too many arguments\n", 26);
		return (1);
	}
	exit(exit_code);
}
