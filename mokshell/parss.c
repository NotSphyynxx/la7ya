/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parss.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:07:20 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/09 17:07:23 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_single_redirection(t_token **tokens, char *line, int *i)
{
	char	*op;
	t_type	type;

	op = malloc(2 * sizeof(char));
	if (!op)
		return (0);
	op[0] = line[*i];
	op[1] = '\0';
	if (line[*i] == '>')
		type = REDIR_OUT;
	else
		type = REDIR_IN;
	add_token(tokens, new_token(op, type));
	free(op);
	(*i)++;
	return (1);
}

int	check_heredoc(t_token **tokens, char *line, int *i)
{
	char	*op;

	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		op = ft_strdup(">>");
		if (!op)
			return (0);
		add_token(tokens, new_token(op, REDIR_APPEND));
		free(op);
		*i += 2;
	}
	else if (line[*i] == '<' && line[*i + 1] == '<')
	{
		op = ft_strdup("<<");
		if (!op)
			return (0);
		add_token(tokens, new_token(op, HEREDOC));
		free(op);
		*i += 2;
	}
	else
		return (handle_single_redirection(tokens, line, i));
	return (1);
}
static void	remove_quotes_tokens(t_token *tokens)
{
	char	*stripped;

	while (tokens)
	{
		if (tokens->type == WORD)
		{
			stripped = ft_strip_quotes(tokens->value);
			free(tokens->value);
			tokens->value = stripped;
		}
		tokens = tokens->next;
	}
}

t_token *parss(char *line)
{
	t_token	*tokens;
	int	i;

	tokens = NULL;
	i = 0;
	if (!check_all(&tokens, line, &i))
		return (NULL);
	if (check_syntax(tokens))
	{
		free_tokens(tokens);
		tokens = NULL;
		printf("Invalid syntax.\n");
		set_exit_status(2);
		return (NULL);
	}
	expand(tokens);
	remove_quotes_tokens(tokens);
	*get_token_list() = tokens;
	return (tokens);
}
