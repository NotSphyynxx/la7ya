/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:05:20 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/05/13 16:03:24 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handle_heredocs(t_token *tokens)
{
    t_token *curr = tokens;
    int tmp_fd;
    char *line;

    while (curr)
    {
        if (curr->type == HEREDOC)
        {
            // Create a temporary file to store heredoc contents
            tmp_fd = open("/tmp/.heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (tmp_fd < 0)
            {
                perror("heredoc tmp file error");
                return;
            }

            // Read lines from stdin until the heredoc delimiter is encountered
            while (1)
            {
                line = readline("> ");
                if (!line || ft_strcmp(line, curr->next->value) == 0)
                {
                    free(line);
                    break; // Stop reading when we reach the delimiter
                }
                write(tmp_fd, line, ft_strlen(line));
                write(tmp_fd, "\n", 1);
                free(line);
            }

            // Close the tmp file where heredoc content was written
            close(tmp_fd);

            // Replace the HEREDOC token with REDIR_IN type and point it to the temporary file
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
