/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper_8.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:58:33 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/08 15:57:21 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	should_count_token(t_token *t)
{
	char	*clean;

	if (t->type != WORD && t->type != ENV_VAR)
		return (0);
	clean = t->value;
	if (!t->was_single && !t->was_double)
		while (*clean == ' ')
			clean++;
	if (*clean == '\0')
		return (0);
	return (1);
}

int	count_args(t_token *start, t_token *end)
{
	int		count;
	t_token	*t;
	char	*clean;

	count = 0;
	t = start;
	while (t && t != end)
	{
		if (should_count_token(t))
		{
			clean = t->value;
			count += is_token_assign_or_space(t, clean);
		}
		else if (t->type == REDIR_OUT || t->type == REDIR_APPEND
			|| t->type == REDIR_IN || t->type == HEREDOC)
			t = t->next;
		t = t->next;
	}
	return (count);
}

void	add_token_to_args(t_token *t, char **cmd, int *i)
{
	char	*clean;
	char	**parts;
	int		j;

	clean = t->value;
	if (!t->was_single && !t->was_double)
		while (*clean == ' ')
			clean++;
	if (!t->was_single && !t->was_double
		&& !is_assignment(clean) && ft_strchr(clean, ' '))
	{
		parts = split_on_spaces(clean);
		if (parts)
		{
			j = 0;
			while (parts[j])
				cmd[(*i)++] = ft_strdup(parts[j++]);
			ft_free_str_array(parts);
		}
	}
	else
		cmd[(*i)++] = ft_strdup(clean);
}

void	fill_args(t_token *start, t_token *end, char **cmd)
{
	int		i;
	t_token	*t;

	i = 0;
	t = start;
	while (t && t != end)
	{
		if (should_count_token(t))
			add_token_to_args(t, cmd, &i);
		else if (t->type == REDIR_OUT || t->type == REDIR_APPEND
			|| t->type == REDIR_IN || t->type == HEREDOC)
			t = t->next;
		t = t->next;
	}
	cmd[i] = NULL;
}

char	**tokens_to_cmd(t_token *start, t_token *end)
{
	int		count;
	char	**cmd;

	count = count_args(start, end);
	if (count == 0)
		return (NULL);
	cmd = malloc(sizeof(char *) * (count + 1));
	if (!cmd)
		return (NULL);
	fill_args(start, end, cmd);
	if (!cmd[0])
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
}
