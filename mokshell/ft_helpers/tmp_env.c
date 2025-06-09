/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 15:00:12 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/08 16:17:21 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	***get_env(void)
{
	static char	**env;

	return (&env);
}

char	*get_env_value(char *key)
{
	char	**env;
	int		i;
	int		len;

	env = *get_env();
	len = ft_strlen(key);
	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], key, len) && env[i][len] == '=')
		{
			return (env[i] + len + 1);
		}
		i++;
	}
	return (NULL);
}

t_exp	**get_exp_list(void)
{
	static t_exp	*exp_list;

	return (&exp_list);
}

char	**init_env(char **envp)
{
	int		i;
	char	**new_env;

	i = 0;
	if (!envp || !envp[0])
	{
		return (create_minimal_env());
	}
	while (envp[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
	{
		write(2, "malloc error\n", 14);
		return (NULL);
	}
	i = 0;
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	init_export_list(void)
{
	char	**env;
	int		i;
	t_exp	*node;

	env = *get_env();
	i = 0;
	while (env && env[i])
	{
		node = split_env_to_exp(env[i]);
		add_exp_back(get_exp_list(), node);
		i++;
	}
}
