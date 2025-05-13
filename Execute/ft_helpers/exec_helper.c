/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:28:27 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/05/13 17:47:53 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_check(char **input, char **envp)
{
    printf("here2\n");
    if (!input || !(*input))
        return (0);
    else if (ft_strcmp(input[0], "echo") == 0)
        return (shell_echo(input), 1);
    else if (ft_strcmp(input[0], "env") == 0)
        return (shell_env(input, envp), 1);
    else if (ft_strcmp(input[0], "pwd") == 0)
        return (shell_pwd(input), 1);
    else if (ft_strcmp(input[0], "cd") == 0)
        return (shell_cd(input), 1);
    else if (ft_strcmp(input[0], "export") == 0)
        return (shell_export(input), 1);
    else if (ft_strcmp(input[0], "unset") == 0)
        return (shell_unset(input), 1);
    else if (ft_strcmp(input[0], "exit") == 0)
        return (shell_exit(input), 1);
    return (0);
}


void ft_free_str_array(char **arr)
{
    int i = 0;
    while (arr && arr[i])
    {
        free(arr[i++]);
    }
    free(arr);
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

char **tokens_to_cmd(t_token *start, t_token *end)
{
    int count = 0;
    t_token *temp = start;

    // Count number of WORD tokens
    while (temp != end)
    {
        if (temp->type == WORD)
            count++;
        temp = temp->next;
    }

    // Allocate command array
    char **cmd = malloc(sizeof(char *) * (count + 1));
    if (!cmd)
        return (NULL);

    temp = start;
    int i = 0;

    // Add words into cmd array
    while (temp != end)
    {
        if (temp->type == WORD)
            cmd[i++] = ft_strdup(temp->value);
        else if (temp->type == REDIR_OUT || temp->type == REDIR_APPEND ||
                 temp->type == REDIR_IN || temp->type == HEREDOC)
            temp = temp->next;  // skip the next token (target)
        temp = temp->next;
    }

    cmd[i] = NULL;
    return (cmd);
}



