/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:59:36 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/11 08:54:24 by ilarhrib         ###   ########.fr       */
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

static void	check_expand_flag(t_token *tok)
{
	int		i;
	char	quote;
	int		has_expand;

	i = 0;
	quote = 0;
	has_expand = 0;
	while (tok->value[i])
	{
		if (tok->value[i] == '\'' && quote == 0)
			quote = '\'';
		else if (tok->value[i] == '\'' && quote == '\'')
			quote = 0;
		else if (tok->value[i] == '$' && quote != '\'')
			has_expand = 1;
		i++;
	}
	if (has_expand)
	{
		tok->was_single = 0;
		tok->was_double = 0;
	}
}

void	set_quote_flags(t_token *tok)
{
	int	len;

	if (!tok || !tok->value)
		return ;
	tok->was_single = 0;
	tok->was_double = 0;
	len = ft_strlen(tok->value);
	if (len >= 2 && tok->value[0] == '\'' && tok->value[len - 1] == '\'')
		tok->was_single = 1;
	else if (len >= 2 && tok->value[0] == '"' && tok->value[len - 1] == '"')
		tok->was_double = 1;
	check_expand_flag(tok);
}
