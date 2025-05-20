/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:28:27 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/05/20 17:31:56 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_check(char **input, char **envp)
{
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


char *find_command_path(char *cmd, t_exec *exec)
{
	char *path_env;
	char **paths;
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
		exec->cmnd_path = ft_strjoin(paths[i], "/");
		if (!exec->cmnd_path)
		{
			ft_free_str_array(paths);
			return (NULL);
		}
		exec->cmnd_path = ft_strjoin(exec->cmnd_path, cmd);
		if (!exec->cmnd_path)
		{
			ft_free_str_array(paths);
			return (NULL);
		}
		if (access(exec->cmnd_path, X_OK) == 0)
		{
			ft_free_str_array(paths);
			return (exec->cmnd_path);
		}
		free(exec->cmnd_path);
		i++;
	}
	ft_free_str_array(paths);
	return (NULL);
}

char **tokens_to_cmd(t_token *start, t_token *end)
{
    int count = 0;
    t_token *temp = start;

    while (temp != end && temp)
    {
        if (temp->type == WORD || temp->type == ENV_VAR)
            count++;
        else if (temp->type == REDIR_OUT || temp->type == REDIR_APPEND ||
                 temp->type == REDIR_IN || temp->type == HEREDOC)
            temp = temp->next;  // skip the next token (target)
        temp = temp->next;
    }
    char **cmd = malloc(sizeof(char *) * (count + 1));
    if (!cmd)
        return NULL;
    temp = start;
    int i = 0;
    while (temp != end && temp)
    {
        if (temp->type == WORD || temp->type == ENV_VAR) {
            cmd[i++] = ft_strdup(temp->value); // Use the expanded value
        }
        else if (temp->type == REDIR_OUT || temp->type == REDIR_APPEND ||
                 temp->type == REDIR_IN || temp->type == HEREDOC) {
            temp = temp->next;  // skip the next token (target)
        }
        temp = temp->next;
    }
    cmd[i] = NULL;
    return cmd;
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t 	i;

	i = 0;
	while (s[i] && i < n)
		i++;
	dup = (char *)malloc(sizeof(char) * (i + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
