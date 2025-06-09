/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_builtins_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:56:37 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/09 17:20:55 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_current_pwd(void)
{
	char	*cwd;
	char	*pwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	pwd = ft_strjoin("PWD=", cwd);
	free(cwd);
	return (pwd);
}

static void	add_new_node(char *key, char *val, int append)
{
	if (append && !val)
		val = ft_strdup("");
	if (val)
		add_exp_back(get_exp_list(), new_exp_node(ft_strdup(key),
				ft_strdup(val)));
	else
		add_exp_back(get_exp_list(), new_exp_node(ft_strdup(key), NULL));
}

void	apply_export_list(char *key, char *val, int append)
{
	t_exp	*ex;

	ex = find_exp(*get_exp_list(), key);
	if (ex)
	{
		if (val)
			update_existing_node(ex, val, append);
	}
	else
		add_new_node(key, val, append);
}

int	shell_export(char **av)
{
	int	i;
	int	err;

	i = 1;
	err = 0;
	if (!av[1])
	{
		printf_export_list();
		set_exit_status(0);
		return (0);
	}
	while (av[i])
	{
		handle_export_arg(av[i], &err);
		i++;
	}
	set_exit_status(err);
	return (err);
}
