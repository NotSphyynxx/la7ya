/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper_12.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:58:59 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/08 14:59:00 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_export_node(t_exp **lst, char *key)
{
	t_exp	*cur;
	t_exp	*prev;

	prev = NULL;
	cur = *lst;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				*lst = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

void	handle_export_arg(char *arg, int *err)
{
	int		append;
	char	*key;
	char	*val;

	parse_export_arg(arg, &key, &val, &append);
	if (!check_valid_key(key))
	{
		error_export(&key, &val);
		*err = 2;
	}
	else
		handle_valid_key(key, val, append);
}

void	handle_valid_key(char *key, char *val, int append)
{
	t_exp	*ex;

	apply_export_list(key, val, append);
	if (val)
	{
		if (append)
		{
			ex = find_exp(*get_exp_list(), key);
			sync_env_var(key, ex->value);
		}
		else
			sync_env_var(key, val);
	}
	free(key);
	free(val);
}

void	append_value(t_exp *ex, char *val)
{
	char	*old_val;
	char	*tmp;

	old_val = ex->value;
	if (!old_val)
		old_val = ft_strdup("");
	tmp = ft_strjoin(old_val, val);
	if (!ex->value)
		free(old_val);
	else
		free(ex->value);
	ex->value = tmp;
}

void	update_existing_node(t_exp *ex, char *val, int append)
{
	if (append)
		append_value(ex, val);
	else
	{
		free(ex->value);
		ex->value = ft_strdup(val);
	}
}