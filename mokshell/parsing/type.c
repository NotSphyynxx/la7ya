/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 15:01:23 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/09 23:43:46 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_quotes(t_token *curr, char **tmp, char **to_free)
{
	if (curr->was_double == 1 || curr->was_single == 1)
	{
		*tmp = ft_strip_quotes(curr->value);
		*to_free = *tmp;
		if (*tmp[0] == '$')
			(*tmp)++;
	}
}

char	*type_to_string(t_type type)
{
	if (type == WORD)
		return ("WORD");
	if (type == PIPE)
		return ("PIPE");
	if (type == REDIR_IN)
		return ("REDIR_IN");
	if (type == REDIR_OUT)
		return ("REDIR_OUT");
	if (type == REDIR_APPEND)
		return ("REDIR_APPEND");
	if (type == HEREDOC)
		return ("HEREDOC");
	if (type == ENV_VAR)
		return ("ENV_VAR");
	if (type == SINGLE_QUOTE1)
		return ("SINGLE_QUOTE1");
	if (type == DOUBLE_QUOTE1)
		return ("DOUBLE_QUOTE1");
	if (type == SINGLE_QUOTE2)
		return ("SINGLE_QUOTE2");
	if (type == DOUBLE_QUOTE2)
		return ("DOUBLE_QUOTE2");
	return ("UNKNOWN");
}
