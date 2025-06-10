/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper_6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:58:16 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/10 15:37:18 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	signal(SIGQUIT, SIG_DFL);
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

int	handle_pipe_segment(t_pipe *data, t_token **start,
		t_token *curr, int idx)
{
	pipe(data->fd);
	data->pids[idx] = fork();
	if (data->pids[idx] < 0)
	{
		set_exit_status(1);
		handle_fork_error(idx);
		return (-1);
	}
	if (data->pids[idx] == 0)
		exec_pipe_segment(*start, curr);
	close(data->fd[1]);
	if (data->prev_fd != -1)
		close(data->prev_fd);
	data->prev_fd = data->fd[0];
	*start = curr->next;
	return (0);
}

void	final_exe(t_token *start, t_pipe *data, int idx)
{
	final_pipe_exec(start, idx);
	free(data->pids);
	data->pids = NULL;
	wait_for_children();
}

void	free_line(char **line)
{
	if (*line)
	{
		free(*line);
	}
}
