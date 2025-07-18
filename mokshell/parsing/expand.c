/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 15:01:06 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/11 08:53:12 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env2_value(const char *name)
{
	char	**env;
	int		i;
	char	*equal;
	int		len;

	env = *get_env();
	i = 0;
	while (env[i])
	{
		equal = ft_strchr(env[i], '=');
		if (equal)
		{
			len = equal - env[i];
			if (ft_strncmp(name, env[i], len) == 0
				&& ft_strlen(name) == (size_t)len)
				return (equal + 1);
		}
		i++;
	}
	return ("");
}

void	handle_expansion(t_token *tokens, int *flag)
{
	t_token	*curr;
	char	*expanded;

	curr = tokens;
	while (curr)
	{
		if (curr->type == WORD && !curr->was_single
			&& ft_strchr(curr->value, '$'))
		{
			*get_line_to_expand() = curr->value;
			expanded = expand_variable(*get_line_to_expand(), flag);
			free(curr->value);
			curr->value = expanded;
		}
		curr = curr->next;
	}
}

void	expand(t_token *tokens)
{
	t_token	*curr;
	int		flag;

	flag = 0;
	handle_expansion(tokens, &flag);
	curr = tokens;
	while (curr)
	{
		if (curr->type == REDIR_IN || curr->type == REDIR_OUT
			|| curr->type == REDIR_APPEND || curr->type == HEREDOC)
		{
			if (!curr->next || !curr->next->value
				|| ft_strlen(curr->next->value) == 0
				|| wf_name(curr->next->value, flag) == 1)
				if (curr->next)
					curr->next->ambigious = 1;
		}
		curr = curr->next;
	}
}
