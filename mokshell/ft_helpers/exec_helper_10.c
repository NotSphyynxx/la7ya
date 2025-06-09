/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper_10.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:58:49 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/09 22:39:26 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_assignment(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == ' ' || str[i] == '\t')
			return (0);
		i++;
	}
	if (str[i] == '=')
		return (1);
	return (0);
}

int	adjust_env(char *var, char *name)
{
	char	**env;
	int		i;

	i = 0;
	env = *get_env();
	while (env[i])
	{
		if (exist_check(env[i], name))
		{
			free(env[i]);
			env[i] = ft_strdup(var);
			return (1);
		}
		i++;
	}
	if (!env || !env[i])
	{
		if (realloc_env(var))
			return (1);
	}
	return (0);
}

int	exist_check(char *env_entry, char *name)
{
	int	len;

	len = ft_strlen(name);
	if (ft_strncmp(env_entry, name, len) == 0
		&& env_entry[len] == '=')
		return (1);
	return (0);
}

char	**get_pwd_storage(void)
{
	static char	*pwd;

	return (&pwd);
}

void	free_pwd_storage(void)
{
	free(*get_pwd_storage());
	*get_pwd_storage() = NULL;
}
