/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parss_helper_10.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:59:51 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/08 14:59:52 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_quotes(t_token *curr, char **tmp, char **to_free)
{
	if (curr->was_double == 1 || curr->was_single == 1)
	{
		*tmp = ft_strip_quotes(curr->value);
		*to_free = *tmp;
		if (*tmp[0] == '$')
			(*tmp)++;
	}
}

static int	is_delimiter(t_token *curr, char *line, char *tmp)
{
	if (!line)
		return (1);
	if (!ft_strcmp(line, curr->value))
		return (1);
	if (tmp && !ft_strcmp(line, tmp))
		return (1);
	return (0);
}

static void	process_line(t_token *curr, int fd, char *line)
{
	char	*temp_line;

	if (curr->was_double == 0 && curr->was_single == 0)
	{
		temp_line = line;
		line = expand_var(line);
		free(temp_line);
	}
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
}

int	open_heredoc_file(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("heredoc tmp file error");
		exit(1);
	}
	return (fd);
}

static void	heredoc_loop(t_token *curr, int fd, char *tmp)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (is_delimiter(curr, line, tmp))
		{
			free(line);
			break;
		}
		process_line(curr, fd, line);
	}
}

void	handle_heredoc_child(t_token *curr, char *filename)
{
	int		fd;
	char	*tmp;
	char	*to_free;

	tmp = NULL;
	to_free = NULL;
	fd = open_heredoc_file(filename);
	curr = curr->next;
	handle_quotes(curr, &tmp, &to_free);
	heredoc_loop(curr, fd, tmp);
	if (to_free)
		free(to_free);
	close(fd);
	exit(0);
}
