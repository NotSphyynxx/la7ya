/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper_15.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:55:17 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/11 06:30:47 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_pipe_segment(t_token *start, t_token *end)
{
	t_pipe	*data;
	char	**cmd;

	data = get_pipe_data();
	if (data->prev_fd != -1)
		dup2(data->prev_fd, STDIN_FILENO);
	dup2(data->fd[1], STDOUT_FILENO);
	close(data->fd[0]);
	close(data->fd[1]);
	if (data->prev_fd != -1)
		close(data->prev_fd);
	cmd = tokens_to_cmd(start, end);
	signal(SIGQUIT, SIG_DFL);
	execute(cmd, start, end);
	ft_free_str_array(cmd);
	exit(0);
}

void	kill_all_pids(int idx)
{
	t_pipe	*data;
	int		i;

	data = get_pipe_data();
	i = 0;
	while (i < idx)
	{
		kill(data->pids[i], SIGTERM);
		waitpid(data->pids[i], NULL, 0);
		i++;
	}
}

void	cleanup_pipes(void)
{
	t_pipe	*data;

	data = get_pipe_data();
	if (data->pids)
		free(data->pids);
	if (data->prev_fd != -1)
		close(data->prev_fd);
	data->pids = NULL;
	data->prev_fd = -1;
}

void	handle_fork_error(int idx)
{
	t_pipe	*d;

	d = get_pipe_data();
	if (!d->error_reported)
	{
		perror("fork");
		d->error_reported = 1;
	}
	kill_all_pids(idx);
	if (d->prev_fd != -1)
		close(d->prev_fd);
	if (d->fd[0])
		close(d->fd[0]);
	if (d->fd[1])
		close(d->fd[1]);
	free(d->pids);
	d->pids = NULL;
}

void	final_pipe_exec(t_token *start, int idx)
{
	t_pipe		*data;
	char		**cmd;

	data = get_pipe_data();
	data->pids[idx] = fork();
	if (data->pids[idx] < 0)
		return (handle_fork_error(idx));
	if (data->pids[idx] == 0)
	{
		if (data->prev_fd != -1)
			dup2(data->prev_fd, STDIN_FILENO);
		if (data->prev_fd != -1)
			close(data->prev_fd);
		cmd = tokens_to_cmd(start, NULL);
		if (cmd)
		{
			signal(SIGQUIT, SIG_DFL);
			execute(cmd, start, NULL);
		}
		ft_free_str_array(cmd);
		exit(0);
	}
	if (data->prev_fd != -1)
		close(data->prev_fd);
}
