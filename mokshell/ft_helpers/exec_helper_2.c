/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:05:20 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/05/21 16:49:55 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *make_heredoc_filename(int count)
{
	char	*prefix = "/tmp/.heredoc_tmp_";
	char	*num_str;
	char	*filename;

	num_str = ft_itoa(count);
	if (!num_str)
		return NULL;
	filename = ft_strjoin(prefix, num_str);
	free(num_str);
	return filename;
}
static void	handle_heredoc_child(t_token *curr, int count)
{
	int		fd;
	char	*filename;
	char	*line;

	filename = make_heredoc_filename(count);
	if (!filename)
		exit(1);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(filename);
	if (fd < 0)
	{
		perror("heredoc tmp file error");
		exit(1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, curr->next->value) == 0)
		{
			free(line);
			break;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	exit(0);
}

void	handle_heredocs_range(t_token *start, t_token *end)
{
	t_token		*curr;
	pid_t		pid;
	int			status;
	static int	count;
	char		*filename;

	curr = start;
	while (curr && curr != end)
	{
		if (curr->type == HEREDOC)
		{
			pid = fork();
			if (pid == 0)
				handle_heredoc_child(curr, count);
			waitpid(pid, &status, 0);
			update_exit_status(status);
			filename = make_heredoc_filename(count);
			if (filename)
			{
				free(curr->next->value);
				curr->next->value = filename;
			}
			curr->type = REDIR_IN;
			count++;
		}
		curr = curr->next;
	}
}

int contains_pipe_in_tokens(t_token *tokens)
{
	t_token *curr = tokens;
	while (curr)
	{
		if (curr->type == PIPE)
			return 1;
		curr = curr->next;
	}
	return 0;
}

void	printf_export_list(void)
{
	t_exp *env;

	env = *get_exp_list();
	while(env)
	{
		write(1, "declare -x ", 11);
		write(1, env->key, ft_strlen(env->key));
		if (env->value)
		{
			write(1, "=\"", 2);
			write(1, env->value, ft_strlen(env->value));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		env = env->next;
	}
}

t_exp	*new_exp_node(char *key, char *value)
{
	t_exp	*node;

	node = malloc(sizeof(t_exp));
	if (!node)
	{
		update_exit_status(2);
		return (NULL);
	}
    node->key = key;
    node->value = value;
	node->next = NULL;
	return (node);
}