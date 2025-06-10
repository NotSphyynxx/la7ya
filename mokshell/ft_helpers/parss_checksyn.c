/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parss_checksyn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:59:44 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/10 15:20:43 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_first_token_pipe(t_token *token)
{
	if (token && token->type == PIPE)
	{
		printf("Syntax error: unexpected '|' \n");
		return (1);
	}
	return (0);
}

static int	check_pipe_errors(t_token *current)
{
	if (current->type == PIPE
		&& current->next && current->next->type == PIPE)
	{
		printf("Syntax error: unexpected '||' \n");
		return (1);
	}
	if (current->type == PIPE && current->next == NULL)
	{
		printf("Syntax error: unexpected '|' \n");
		return (1);
	}
	return (0);
}

static int	check_redirection_errors(t_token *current)
{
	if ((current->type == REDIR_IN || current->type == REDIR_OUT
			|| current->type == REDIR_APPEND || current->type == HEREDOC)
		&& (current->next == NULL || current->next->type != WORD))
	{
		printf("Syntax error: missing file after redirection\n");
		return (1);
	}
	return (0);
}

int	check_syntax(t_token *tokens)
{
	t_token	*current;
	int		i;

	if (is_first_token_pipe(tokens))
		return (1);
	current = tokens;
	while (current)
	{
		if (current->type == HEREDOC && current->next
			&& current->next->type == WORD)
			i = handle_heredocs_range(current);
		if (i == 7)
			return (7);
		if (check_pipe_errors(current)
			|| check_redirection_errors(current))
			return (1);
		current = current->next;
	}
	return (0);
}
