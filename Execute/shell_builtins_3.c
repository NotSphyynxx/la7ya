/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_builtins_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:53:37 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/05/03 16:53:11 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shift_vars(int index, int count)
{
	char **env = *get_env();
	int i = index;

	while (i < count - 1)
	{
		env[i] = env[i + 1];
		i++;
	}
	env[count - 1] = NULL;
}

static void	remove_env_var(char *name)
{
	char **env = *get_env();
	int i = 0;
	int count = 0;

	while(env && env[count])
		count++;
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, ft_strlen(name)) && env[i][ft_strlen(name)])
		{
			shift_vars(i, count);
			return ;
		}
		i++;
	}
}

int	shell_unset(char **av)
{
	int			i;
	char	*name;

	if (!av[1])
	{
		write(STDERR_FILENO, "unset: not enough arguments\n", 28);
		return (1);
	}
	i = 1;
	while (av[i])
	{
		name = av[i];
	
		char *name_ptr = name;
		while (*name_ptr)
		{
			if (!ft_isalnum(*name_ptr) && *name_ptr != '_')
			{
				write(STDERR_FILENO, "unset: invalid name\n", 21);
				return (1);
			}
			name_ptr++;
		}
		remove_env_var(name);
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