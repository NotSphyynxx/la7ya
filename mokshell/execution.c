/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:24:48 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/05/21 16:20:17 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmnd_check(char **input, char **envp, t_token *tokens, t_exec *exec)
{
	if (tokens)
	{
		if (contains_pipe_in_tokens(tokens))
			execute_pipe_commands(tokens, exec);
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
				executor_simple_command(tokens, exec);
		}
	}
}

void	execute(char **input, t_token *start, t_token *end, t_exec *exec)
{
	char	*path;

	if (apply_redirections(start, end) == -1)
		exit(1);
	if (builtin_check(input, *get_env()))
		exit(0);
	path = find_command_path(input[0], exec);
	if (!path)
	{
		write(STDERR_FILENO, "minishell: command not found\n", 29);
		exit(127);
	}
	if (access(path, X_OK) != 0)
	{
		perror("minishell");
		exit(126);
	}
	execve(path, input, *get_env());
	perror("execve failed");
	exit(126);
}

void	execute_pipe_commands(t_token *tokens, t_exec *exec)
{
	t_token	*curr;
	t_token	*start;
	int		fd[2];
	int		prev_fd;

	curr = tokens;
	start = tokens;
	prev_fd = -1;
	while (curr)
	{
		if (curr->type == PIPE)
		{
			execute_piped_cmnd(start, curr, prev_fd, fd, exec);
			close(fd[1]);
			if (prev_fd != -1)
				close(prev_fd);
			prev_fd = fd[0];
			start = curr->next;
		}
		curr = curr->next;
	}
	execute_final_command(start, prev_fd, exec);
	if (prev_fd != -1)
		close(prev_fd);
	wait_for_children();
}

void	executor_simple_command(t_token *tokens, t_exec *exec)
{
	int status;
	pid_t	pid;

	status = 0;
	(tokens);
	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		return ;
	}
	if (pid == 0)
	{
		executor_child_process(tokens, exec);
	}
	waitpid(pid, &status, 0);
	update_exit_status(status);
}
