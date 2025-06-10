/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parss_helpers_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 15:00:04 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/09 23:41:07 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*collect_word(char *line, int *i)
{
	int		start;
	char	quote;

	start = *i;
	while (line[*i] && !ft_isspace(line[*i]) && !ft_strchr("|<>", line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '"')
		{
			quote = line[(*i)++];
			while (line[*i] && line[*i] != quote)
				(*i)++;
			if (line[*i] == quote)
				(*i)++;
		}
		else
			(*i)++;
	}
	return (ft_substr(line, start, *i - start));
}

int	has_unclosed_quote(const char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && quote == 0)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		i++;
	}
	return (quote != 0);
}

int	last_check(t_token **tokens, char *line, int *i)
{
	char	*word;
	t_token	*tok;

	tok = NULL;
	word = collect_word(line, i);
	if (!word)
		return (1);
	if (has_unclosed_quote(word))
	{
		write(STDERR_FILENO, "minishell: syntax error: unclosed quote\n", 40);
		free(word);
		free_tokens(*tokens);
		set_exit_status(2);
		free_tokens(tok);
		return (1);
	}
	tok = new_token(word, WORD);
	set_quote_flags(tok);
	add_token(tokens, tok);
	free(word);
	return (0);
}

void	free_exp(t_exp *exp)
{
	t_exp	*tmp;

	while (exp)
	{
		tmp = exp->next;
		if (exp->key)
			free(exp->key);
		if (exp->value)
			free(exp->value);
		free(exp);
		exp = tmp;
	}
}
