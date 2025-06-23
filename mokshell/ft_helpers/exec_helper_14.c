/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper_14.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 21:33:19 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/11 10:22:52 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_check(void)
{
	t_token	*tokens;

	if (ft_strcmp(*get_line(), "cd \"\"") == 0
		|| ft_strcmp(*get_line(), "cd \'\'") == 0)
	{
		set_exit_status(0);
		return (1);
	}
	if (!*get_line() || ft_strlen(*get_line()) == 0)
	{
		printf("Minishell : command not found\n");
		set_exit_status(127);
		return (1);
	}
	tokens = *get_token_list();
	if ((tokens && tokens->value && ft_strlen(tokens->value) == 0
			&& tokens->next)
		|| ft_strcmp("\"\"", *get_line()) == 0
		|| ft_strcmp("\'\'", *get_line()) == 0)
	{
		printf("Minishell : command not found\n");
		set_exit_status(127);
		return (1);
	}
	return (0);
}

void	execute(char **input, t_token *start, t_token *end)
{
	char	*path;

	if (apply_redirections(start, end) == -1)
		exit(1);
	if (builtin_check(input, *get_env()))
		exit(0);
	path = find_command_path(input[0]);
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
	signal(SIGQUIT, SIG_DFL);
	execve(path, input, *get_env());
	perror("execve failed");
	exit(126);
}

int	count_commands(t_token *tokens)
{
	int	count;

	count = 1;
	while (tokens)
	{
		if (tokens->type == PIPE)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

void	init_pipe_data(int n_cmds)
{
	t_pipe	*data;

	data = get_pipe_data();
	data->n_cmds = n_cmds;
	data->pids = malloc(sizeof(int) * n_cmds);
	data->prev_fd = -1;
	data->error_reported = 0;
}

int	no_number(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isalnum(line[i]))
			return (0);
		i++;
	}
	return (1);
}
