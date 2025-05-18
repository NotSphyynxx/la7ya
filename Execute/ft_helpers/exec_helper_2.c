/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:05:20 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/05/14 17:08:25 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handle_heredocs(t_token *tokens)
{
    t_token *curr = tokens;
    int tmp_fd;
    pid_t pid;

    while (curr)
    {
        if (curr->type == HEREDOC)
        {
            pid = fork();
            if (pid == 0)
            {
                char *line;
                tmp_fd = open("/tmp/.heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (tmp_fd < 0)
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
                    write(tmp_fd, line, ft_strlen(line));
                    write(tmp_fd, "\n", 1);
                    free(line);
                }
                close(tmp_fd);
                exit(0);
            }
            waitpid(pid, NULL, 0); // parent waits for heredoc child to finish
            curr->type = REDIR_IN;
            free(curr->next->value);
            curr->next->value = ft_strdup("/tmp/.heredoc_tmp");
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
		return (NULL);
    node->key = key;
    node->value = value;
	node->next = NULL;
	return (node);
}