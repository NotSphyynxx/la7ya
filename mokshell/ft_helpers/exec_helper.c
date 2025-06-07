/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:28:27 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/05/21 17:21:26 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Check if cmd is a direct path and executable
static char *check_direct_path(char *cmd)
{
    if (access(cmd, X_OK) == 0)
        return (ft_strdup(cmd));
    return (NULL);
}

// Search for command in PATH directories
static char *search_in_path(char *cmd, char **paths, t_exec *exec)
{
    int     i;
    char    *tmp;

    i = 0;
    while (paths[i])
    {
        tmp = ft_strjoin(paths[i], "/");
        if (!tmp)
            return (NULL);
        exec->cmnd_path = ft_strjoin(tmp, cmd);
        free(tmp);
        if (!exec->cmnd_path)
            return (NULL);
        if (access(exec->cmnd_path, X_OK) == 0)
            return (exec->cmnd_path);
        free(exec->cmnd_path);
        i++;
    }
    return (NULL);
}

// Main command lookup function
char *find_command_path(char *cmd, t_exec *exec)
{
    char    *path_env;
    char    **paths;
    char    *result;

    if (ft_strchr(cmd, '/'))
        return (check_direct_path(cmd));
    path_env = get_env_value("PATH");
    if (!path_env)
        return (NULL);
    paths = ft_split(path_env, ':');
    if (!paths)
        return (NULL);
    result = search_in_path(cmd, paths, exec);
    ft_free_str_array(paths);
    return (result);
}

int	check_valid_key(char *key)
{
	if (!ft_isalpha(*key) && *key != '_')
		return (0);
	while(*key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (0);
		key++;
	}
	return (1);
}

t_exp	*find_exp(t_exp *list, char *key)
{
	while (list)
	{
		if (ft_strcmp(list->key, key) == 0)
			return (list);
		list = list->next;
	}
	return (NULL);
}
