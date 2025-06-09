/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:59:36 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/09 23:38:13 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	if (g_flag_signal == 1)
		return ;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	set_exit_status(1);
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		if (tokens->value)
			free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	set_quote_flags(t_token *tok)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	if (!tok || !tok->value)
		return ;
	while (tok->value[i])
	{
		if ((tok->value[i] == '\'' || tok->value[i] == '"') && quote == 0)
		{
			quote = tok->value[i];
			if (quote == '\'')
				tok->was_single = 1;
			else if (quote == '"')
				tok->was_double = 1;
		}
		else if (tok->value[i] == quote)
			quote = 0;
		i++;
	}
}
