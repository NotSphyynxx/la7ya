/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 15:00:56 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/08 15:00:57 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	append_exit_status_var(char **result, int *i)
{
	char	*tmp;
	char	*exit_status_str;

	exit_status_str = ft_itoa(get_shell()->exit_status);
	tmp = *result;
	*result = ft_strjoin(tmp, exit_status_str);
	free(tmp);
	free(exit_status_str);
	(*i)++;
}

static void	append_named_variable(char **result, char *line, int *i)
{
	int		var_start;
	char	*var_name;
	char	*val;
	char	*tmp;

	var_start = *i;
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		(*i)++;
	var_name = ft_substr(line, var_start, *i - var_start);
	val = ft_strdup(get_env2_val(var_name));
	tmp = *result;
	*result = ft_strjoin(tmp, val);
	free(tmp);
	free(val);
	free(var_name);
}

static void	handle_dollar_case(char *line, int *i, int *start, char **result)
{
	char	*before;
	char	*tmp;

	before = ft_substr(line, *start, *i - *start);
	tmp = *result;
	*result = ft_strjoin(tmp, before);
	free(tmp);
	free(before);
	(*i)++;
	if (line[*i] == '?')
		append_exit_status_var(result, i);
	else if (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		append_named_variable(result, line, i);
	else
	{
		tmp = *result;
		*result = ft_strjoin(tmp, "$");
		free(tmp);
	}
	*start = *i;
}

static void	append_remaining_text(char *line, int i, int start, char **result)
{
	char	*remaining;
	char	*tmp;

	if (start < i)
	{
		remaining = ft_substr(line, start, i - start);
		tmp = *result;
		*result = ft_strjoin(tmp, remaining);
		free(tmp);
		free(remaining);
	}
}

char	*expand_var(char *line)
{
	int		i;
	int		start;
	char	*result;

	i = 0;
	start = 0;
	result = ft_strdup("");
	while (line[i])
	{
		if (line[i] == '$')
			handle_dollar_case(line, &i, &start, &result);
		else
			i++;
	}
	append_remaining_text(line, i, start, &result);
	return (result);
}
