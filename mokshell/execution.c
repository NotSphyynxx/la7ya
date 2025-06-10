/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 15:01:33 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/10 15:34:17 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmnd_check(char **input, char **envp, t_token *tokens)
{
	g_flag_signal = 1;
	if (tokens && !handle_check())
	{
		if (contains_pipe_in_tokens(tokens))
			execute_pipe_commands(tokens);
		else
		{
			if (is_builtin(input))
			{
				if (there_is_red(tokens))
					built_with_red_check(input, envp, tokens);
				else
					builtin_check(input, envp);
			}
			else
				executor_simple_command(tokens);
		}
	}
	g_flag_signal = 0;
}

t_pipe	*get_pipe_data(void)
{
	static t_pipe	data;

	return (&data);
}

void	execute_pipe_commands(t_token *tokens)
{
	t_pipe		*data;
	t_token		*curr;
	t_token		*start;
	int			idx;

	data = get_pipe_data();
	init_pipe_data(count_commands(tokens));
	curr = tokens;
	start = tokens;
	idx = 0;
	while (curr)
	{
		if (curr->type == PIPE)
		{
			if (handle_pipe_segment(data, &start, curr, idx) == -1)
			{
				free(data->pids);
				data->pids = NULL;
				return ;
			}
			idx++;
		}
		curr = curr->next;
	}
	final_exe(start, data, idx);
}

void	executor_simple_command(t_token *tokens)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		set_exit_status(1);
		return ;
	}
	if (pid == 0)
	{
		executor_child_process(tokens);
	}
	waitpid(pid, &status, 0);
	update_exit_status(status);
}
