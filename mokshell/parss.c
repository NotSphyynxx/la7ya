/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parss.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 06:10:41 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/07/08 12:16:19 by bael-bad         ###   ########.fr       */
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

t_token	*parss(char *line)
{
	t_token	*tokens;
	int		i;
	int		flag;

	tokens = NULL;
	i = 0;
	if (!check_all(&tokens, line, &i))
		return (NULL);
	flag = check_syntax(tokens);
	if (flag == 7)
	{
		free_tokens(tokens);
		tokens = NULL;
		set_exit_status(1);
		return (NULL);
	}
	else if (flag == 1)
	{
		handle_error(tokens);
		return (NULL);
	}
	expand(tokens);
	remove_quotes_tokens(tokens);
	*get_token_list() = tokens;
	return (tokens);
}
