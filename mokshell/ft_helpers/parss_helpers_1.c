/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parss_helpers_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:59:58 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/08 14:59:59 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*make_heredoc_filename(void)
{
	int     i;
	char    *num;
	char    *tmp;
	char    *path;

	i = 0;
	while (1)
	{
		num = ft_itoa(i);
		if (!num)
			return NULL;
		tmp = ft_strjoin("/tmp/.heredoc_tmp_", num);
		free(num);
		if (!tmp)
			return NULL;
		if (access(tmp, F_OK) != 0)
		{
			path = tmp;
			break;
		}
		free(tmp);
		i++;
	}
	return path;
}

void	handle_heredocs_range(t_token *curr)
{
	pid_t    pid;
	int      status;
	char    *filename;

	if (curr->type == HEREDOC)
	{
		filename = make_heredoc_filename();
		if (!filename)
			return;
		pid = fork();
		if (pid == 0)
			handle_heredoc_child(curr, filename);
		waitpid(pid, &status, 0);
		update_exit_status(status);
		free(curr->next->value);
		curr->next->value = filename;
		curr->type = REDIR_IN;
	}
}

int check_all(t_token **tokens, char *line, int *i)
{
	while (line[*i])
	{
		if (ft_isspace(line[*i]))
		{
			(*i)++;
			continue;
		}
		if (line[*i] == '|')
		{
			if (!check_pipe(tokens, line, i))
				return (0);
		}
		else if (line[*i] == '>' || line[*i] == '<')
		{
			if (!check_heredoc(tokens, line, i))
				return (0);
		}
		else
		if (last_check(tokens, line, i) == 1)
			return 0;
	}
	return 1;
}

int	check_pipe(t_token **tokens, char *line, int *i)
{
	if (line[*i + 1] == '|')
	{
		printf("Syntax error: unexpected token '||'\n");
		return 0;
	}
	add_token(tokens, new_token("|", PIPE));
	(*i)++;
	return 1;
}

void set_exit_status(int status)
{
	get_shell()->exit_status = status;
}
