/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_builtins_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:57:01 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/08 16:32:17 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	search_then_unset(char **env, char *name)
{
	int	i;
	int	j;
	int	len;

	len = ft_strlen(name);
	i = 0;
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

int	shell_unset(char **av)
{
	int		i;
	int		ret;
	char	*key;

	i = 1;
	ret = 0;
	while (av[i])
	{
		key = av[i];
		if (ft_strchr(key, '='))
		{
			write(STDERR_FILENO,
				"unset: not a valid identifier\n", 31);
			ret = 1;
		}
		else
		{
			search_then_unset(*get_env(), key);
			remove_export_node(get_exp_list(), key);
		}
		i++;
	}
	set_exit_status(ret);
	return (ret);
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

	write(STDOUT_FILENO, "exit\n", 6);
	if (!av[1])
		clean_exit(0);
	exit_code = ft_atoi_with_overflow(av[1], &overflow);
	if (overflow)
	{
		write(STDERR_FILENO, "exit: numeric argument required\n", 33);
		clean_exit(255);
	}
	if (av[2])
	{
		write(STDERR_FILENO, "exit: too many arguments\n", 26);
		return (1);
	}
	clean_exit((unsigned char)exit_code);
	return (0);
}

char	**create_minimal_env(void)
{
	char	**env;

	env = malloc(sizeof(char *) * 4);
	if (!env)
	{
		write(2, "malloc error\n", 14);
		return (NULL);
	}
	env[0] = get_current_pwd();
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("_=./minishell");
	env[3] = NULL;
	if (!env[0] || !env[1] || !env[2])
	{
		ft_free_str_array(env);
		return (NULL);
	}
	return (env);
}
