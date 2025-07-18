/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:57:37 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/09 17:24:12 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_echo_args(char **av, int i)
{
	while (av[i])
	{
		if (av[i][0] != '\0')
		{
			write(STDOUT_FILENO, av[i], ft_strlen(av[i]));
			if (av[i + 1])
				write(STDOUT_FILENO, " ", 1);
		}
		i++;
	}
}

int	shell_echo(char **av)
{
	int	i;
	int	j;
	int	new_line;

	i = 1;
	new_line = 1;
	while (av[i] && av[i][0] == '-' && av[i][1] == 'n')
	{
		j = 1;
		while (av[i][j] == 'n')
			j++;
		if (av[i][j] != '\0')
			break ;
		new_line = 0;
		i++;
	}
	print_echo_args(av, i);
	if (new_line)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}

int	shell_env(char **av, char **envp)
{
	char	**env;

	if (av[1])
	{
		write(STDERR_FILENO, "env: ", 5);
		write(STDERR_FILENO, av[1], ft_strlen(av[1]));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		set_exit_status(127);
		return (127);
	}
	env = envp;
	while (*env)
	{
		write(STDOUT_FILENO, *env, ft_strlen(*env));
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
	set_exit_status(0);
	return (0);
}

int	shell_pwd(char **av)
{
	(void)av;
	printf("%s\n", *get_pwd_storage());
	return (0);
}

int	shell_cd(char **args)
{
	char	*path;

	path = cd_check_args_and_get_path(args);
	if (!path)
		return (1);
	if (chdir(path) == 0)
	{
		update_pwd_on_cd(path);
		return (0);
	}
	if (ft_strcmp(path, "..") == 0)
	{
		update_pwd_on_cd(path);
		return (0);
	}
	perror("cd");
	return (1);
}
