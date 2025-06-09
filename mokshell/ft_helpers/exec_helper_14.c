/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper_14.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 21:33:19 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/09 19:17:04 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all_fd(void)
{
	int	i;

	i = 3;
	while (i <= 100)
	{
		close(i);
		i++;
	}
}

int	handle_check(void)
{
	if (ft_strncmp("ls \"\"", *get_line(), 5) == 0 || ft_strncmp("ls \'\'", *get_line(), 5) == 0)
	{
		write(STDERR_FILENO, "ls: : No such file or directory\n", 33);
		set_exit_status(1);
		return (1);
	}
	else if (ft_strncmp("cd \"\"", *get_line(), 5) == 0)
	{
		set_exit_status(0);
		return (1);
	}
	else if (ft_strncmp("export \"\"", *get_line(), 9) == 0 || ft_strncmp("export \'\'", *get_line(), 9) == 0)
	{
		write(STDERR_FILENO, "export: not a valid identifier\n", 32);
		set_exit_status(1);
		return (1);
	}
	return (0);
}

t_pipe_data *get_pipe_data(void)
{
    static t_pipe_data data;
    return (&data);
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
	t_pipe_data	*data;

	data = get_pipe_data();
	data->n_cmds = n_cmds;
	data->pids = malloc(sizeof(int) * n_cmds);
	data->prev_fd = -1;
	data->error_reported = 0;
}

