/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:28:27 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/05/05 15:54:30 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_check(char **input, char **envp)
{
	if (ft_strcmp(input[0], "echo") == 0)
		shell_echo(input);
	else if (ft_strcmp(input[0], "env") == 0)
		shell_env(input, envp);
	else if (ft_strcmp(input[0], "pwd") == 0)
		shell_pwd(input);
	else if (ft_strcmp(input[0], "cd") == 0)
		shell_cd(input);
	else if (ft_strcmp(input[0], "export") == 0)
		shell_export(input);
	else if (ft_strcmp(input[0], "unset") == 0)
		shell_unset(input);
	else if (ft_strcmp(input[0], "exit") == 0)
		shell_exit(input);
}

void ft_free_str_array(char **array)
{
    int i = 0;

    if (!array)
        return;

    while (array[i]) {
        free(array[i]);
        i++;
    }

    free(array);
}

char *find_command_path(char *cmd)
{
	char *path_env;
	char **paths;
	char *full_path;
	int i;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		if (!full_path)
		{
			ft_free_str_array(paths);
			return (NULL);
		}
		full_path = ft_strjoin(full_path, cmd);
		if (!full_path)
		{
			ft_free_str_array(paths);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
		{
			ft_free_str_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_str_array(paths);
	return (NULL);
}

char **split_command(char **input, int start, int end)
{
    char **cmd;
    int i, count;

    if (end == -1) {
        count = 0;
        while (input[start + count])
            count++;
    } else {
        count = end - start;
    }

    cmd = malloc(sizeof(char *) * (count + 1));
    if (!cmd)
        return (NULL);

    i = 0;
    while (i < count) {
        cmd[i] = ft_strdup(input[start + i]); // Ensure correct memory allocation
        i++;
    }
    cmd[count] = NULL; // Null terminate

    return (cmd);
}

int contains_pipe(char **input)
{
    int i = 0;

    while (input[i]) {
        if (ft_strcmp(input[i], "|") == 0)
            return (1);
        i++;
    }

    return (0);
}
