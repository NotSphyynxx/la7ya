/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper_14.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 21:33:19 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/09 20:37:36 by ilarhrib         ###   ########.fr       */
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
	t_token	*tokens;
	char	*line;

	line = *get_line();
	if (!line || ft_strlen(line) == 0)
	{
		printf("command not found\n");
		set_exit_status(127);
		return (1);
	}
	tokens = *get_token_list();
	if (tokens && tokens->value && ft_strlen(tokens->value) == 0)
	{
		printf("command not found\n");
		set_exit_status(127);
		return (1);
	}
	return (0);
}

t_pipe_data	*get_pipe_data(void)
{
	static t_pipe_data	data;

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
