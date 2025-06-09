/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_coll.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:59:30 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/09 20:28:18 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	gc_clear(char **readed, t_token *tokens, char **input)
{
	if (*readed)
		free(*readed);
	if (tokens)
		free_tokens(tokens);
	ft_free_str_array(input);
	free_all_fd();
}

t_exp	*split_env_to_exp(char *env_entry)
{
	t_exp	*node;
	char	*eq_sign;

	node = malloc(sizeof(t_exp));
	if (!node)
		return (NULL);
	eq_sign = ft_strchr(env_entry, '=');
	if (eq_sign)
	{
		node->key = ft_substr(env_entry, 0, eq_sign - env_entry);
		node->value = ft_strdup(eq_sign + 1);
	}
	else
	{
		node->key = ft_strdup(env_entry);
		node->value = NULL;
	}
	node->next = NULL;
	return (node);
}

void	sync_env_var(char *key, char *val)
{
	char	*prefix;
	char	*entry;

	if (!val)
		return ;
	prefix = ft_strjoin(key, "=");
	if (!prefix)
		return ;
	entry = ft_strjoin(prefix, val);
	free(prefix);
	if (!entry)
		return ;
	adjust_env(entry, key);
	free(entry);
}

void	parse_export_arg(char *arg, char **key, char **val, int *append)
{
	char	*plus;
	char	*eq;

	*append = 0;
	plus = ft_strnstr(arg, "+=", ft_strlen(arg));
	if (plus)
	{
		*append = 1;
		*key = ft_substr(arg, 0, plus - arg);
		*val = ft_strdup(plus + 2);
	}
	else
	{
		eq = ft_strchr(arg, '=');
		if (eq)
		{
			*key = ft_substr(arg, 0, eq - arg);
			*val = ft_strdup(eq + 1);
		}
		else
		{
			*key = ft_strdup(arg);
			*val = NULL;
		}
	}
}
