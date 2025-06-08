/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:57:52 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/08 14:57:53 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	redir_input(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror("open <"), -1);
	if (ft_strncmp(filename, "/tmp/.heredoc_tmp_", 18) == 0)
		unlink(filename);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	redir_output_trunc(const char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("open >"), -1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	redir_output_append(const char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (perror("open >>"), -1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	handle_redirection(t_token *redir)
{
	char	*filename;

	filename = redir->next->value;
	if (redir->type == REDIR_IN)
		return (redir_input(filename));
	if (redir->type == REDIR_OUT)
		return (redir_output_trunc(filename));
	if (redir->type == REDIR_APPEND)
		return (redir_output_append(filename));
	return (0);
}

int	apply_redirections(t_token *start, t_token *end)
{
	t_token	*curr;

	curr = start;
	while (curr && curr != end)
	{
		if (curr->type == REDIR_IN || curr->type == REDIR_OUT
			|| curr->type == REDIR_APPEND)
		{
			if (check_file_token(curr->next) == -1)
				return (-1);
			if (handle_redirection(curr) == -1)
				return (-1);
		}
		curr = curr->next;
	}
	return (0);
}
