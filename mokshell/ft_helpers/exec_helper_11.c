/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper_11.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:58:54 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/08 16:13:58 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	**get_token_list(void)
{
	static t_token	*tokens = NULL;

	return (&tokens);
}

void	free_tokens_list(void)
{
	t_token	*current;
	t_token	*next;

	current = *get_token_list();
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	*get_token_list() = NULL;
}

int	wf_name(char *str, int flag)
{
	int	i;

	i = 0;
	if (!flag)
		return (0);
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

void	update_env_value(char *key, char *value)
{
	char	*var;
	char	*tmp;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return ;
	var = ft_strjoin(tmp, value);
	free(tmp);
	if (!var)
		return ;
	realloc_env(var);
	free(var);
}

void	create_and_fill(char *plus_eq_pos, char **value, char *key)
{
	t_exp	*new_node;
	char	*tmp;

	if (plus_eq_pos)
	{
		add_exp_back(get_exp_list(),
			new_exp_node(ft_strdup(key), ft_strdup("")));
		new_node = find_exp(*get_exp_list(), key);
		if (new_node)
		{
			tmp = new_node->value;
			new_node->value = ft_strjoin(new_node->value, *value);
			free(tmp);
		}
	}
	else
		add_exp_back(get_exp_list(),
			new_exp_node(ft_strdup(key), *value));
}
