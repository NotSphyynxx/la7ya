/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper_6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:58:16 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/08 15:40:21 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	leaks_handle(char *readed, t_token *tokens)
{
	if (readed)
		free(readed);
	if (tokens)
		free_tokens(tokens);
}

void	execute_piped_cmnd(t_token *start, t_token *end, int prev_fd, int fd[2])
{
	pid_t	child_pid;
	char	**cmd;

	pipe(fd);
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		return ;
	}
	if (child_pid == 0)
	{
		if (prev_fd != -1)
			dup2(prev_fd, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		if (prev_fd != -1)
			close(prev_fd);
		cmd = tokens_to_cmd(start, end);
		execute(cmd, start, end);
		ft_free_str_array(cmd);
		exit(0);
	}
}

void	execute_final_command(t_token *start, int prev_fd)
{
	pid_t	child_pid;
	char	**cmd;

	child_pid = fork();
	if (child_pid == 0)
	{
		if (prev_fd != -1)
			dup2(prev_fd, STDIN_FILENO);
		if (prev_fd != -1)
			close(prev_fd);
		cmd = tokens_to_cmd(start, NULL);
		if (!cmd)
			exit(0);
		execute(cmd, start, NULL);
		ft_free_str_array(cmd);
		exit(0);
	}
}

void	executor_child_process(t_token *tokens)
{
	char	**cmd;
	char	*path;

	if (apply_redirections(tokens, NULL) == -1)
		exit(1);
	cmd = tokens_to_cmd(tokens, NULL);
	if (!cmd)
		exit (0);
	if (builtin_check(cmd, *get_env()))
	{
		ft_free_str_array(cmd);
		exit(0);
	}
	path = find_command_path(cmd[0]);
	if (!path)
	{
		write(2, "minishell: command not found\n", 29);
		ft_free_str_array(cmd);
		exit(127);
	}
	execve(path, cmd, *get_env());
	perror("execve failed");
	ft_free_str_array(cmd);
	exit(1);
}

void	ft_free_str_array(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i++]);
	}
	free(arr);
}
