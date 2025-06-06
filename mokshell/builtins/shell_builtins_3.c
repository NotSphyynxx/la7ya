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

#include "../minishell.h"

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

void	clean_exit(int code)
{
	free_tokens_list();
	ft_free_str_array(*get_env());
	free(*get_pwd_storage());
	free_exp(*get_exp_list());
	exit(code);
}
int	shell_exit(char **av)
{
	int			overflow;
	long long	exit_code;

	write(STDOUT_FILENO, "exit\n", 5);
	if (!av[1])
		clean_exit(0);
	exit_code = ft_atoi_with_overflow(av[1], &overflow);
	if (overflow)
	{
		write(2, "exit: numeric argument required\n", 32);
		clean_exit(255);
	}
	if (av[2])
	{
		write(2, "exit: too many arguments\n", 26);
		return (1);
	}
	clean_exit((unsigned char)exit_code);
	return (0);
}
