/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parss_helper_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:52:21 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/07/09 10:55:33 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_status(int status)
{
	status = WEXITSTATUS(status);
	if (status == 1)
		return (7);
	update_exit_status(status);
	return (0);
}

void	handle_error(t_token *tokens)
{
	free_tokens(tokens);
	tokens = NULL;
	printf("Invalid syntax.\n");
}

char	**get_line_to_expand(void)
{
	static char	*exp_line;

	return (&exp_line);
}

int	check_all(t_token **tokens, char *line, int *i)
{
	while (line[*i])
	{
		if (ft_isspace(line[*i]))
		{
			(*i)++;
			continue ;
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
		else if (line[*i] == '"' || line[*i] == '\'')
			token_space(tokens, line, i);
		else
			if (last_check(tokens, line, i) == 1)
				return (0);
	}
	return (1);
}

int	check_pipe(t_token **tokens, char *line, int *i)
{
	if (line[*i + 1] == '|')
	{
		printf("Syntax error: unexpected token '||'\n");
		free_tokens(*tokens);
		set_exit_status(258);
		return (0);
	}
	add_token(tokens, new_token("|", PIPE));
	(*i)++;
	return (1);
}
