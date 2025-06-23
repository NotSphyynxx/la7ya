/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_builtins_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:57:32 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/11 06:40:29 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	pop_last_dir(void)
{
	char	*pwd;
	char	*new;
	int		len;

	pwd = *get_pwd_storage();
	len = ft_strlen(pwd);
	if (len > 1 && pwd[len - 1] == '/')
		len--;
	while (len > 0 && pwd[len - 1] != '/')
		len--;
	if (len == 0)
		len = 1;
	new = ft_substr(pwd, 0, len);
	free(pwd);
	*get_pwd_storage() = new;
}

void	update_pwd_on_cd(char *path)
{
	char	*cwd;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		free(*get_pwd_storage());
		*get_pwd_storage() = cwd;
	}
	else if (ft_strcmp(path, "..") == 0)
		pop_last_dir();
	else if (ft_strcmp(path, ".") != 0)
	{
		tmp = ft_strjoin(*get_pwd_storage(), "/");
		cwd = ft_strjoin(tmp, path);
		free(tmp);
		free(*get_pwd_storage());
		*get_pwd_storage() = cwd;
	}
	update_env_value("PWD", *get_pwd_storage());
}

void	update_pwd_stock(char *new_pwd)
{
	free(*get_pwd_storage());
	*get_pwd_storage() = new_pwd;
}

char	*cd_check_args_and_get_path(char **args)
{
	char	*path;

	if (args[1] && args[2])
	{
		write(2, "cd: too many arguments\n", 24);
		return (NULL);
	}
	if (!args[1])
		path = get_env_value("HOME");
	else
		path = args[1];
	if (!path)
	{
		write(2, "cd: HOME not set\n", 17);
		return (NULL);
	}
	return (path);
}
