/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:05:20 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/05/21 16:49:55 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	contains_pipe_in_tokens(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	while (curr)
	{
		if (curr->type == PIPE)
			return (1);
		curr = curr->next;
	}
	return (0);
}

void	printf_export_list(void)
{
	t_exp	*env;

	env = *get_exp_list();
	while (env)
	{
		write(1, "declare -x ", 11);
		write(1, env->key, ft_strlen(env->key));
		if (env->value)
		{
			write(1, "=\"", 2);
			write(1, env->value, ft_strlen(env->value));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		env = env->next;
	}
}

t_exp	*new_exp_node(char *key, char *value)
{
	t_exp	*node;

	node = malloc(sizeof(t_exp));
	if (!node)
	{
		update_exit_status(2);
		return (NULL);
	}
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

int	builtin_check(char **input, char **envp)
{
	if (!input || !(*input))
	{
		update_exit_status(2);
		return (0);
	}
	else if (ft_strcmp(input[0], "echo") == 0)
		return (shell_echo(input), 1);
	else if (ft_strcmp(input[0], "env") == 0)
		return (shell_env(input, envp), 1);
	else if (ft_strcmp(input[0], "pwd") == 0)
		return (shell_pwd(input), 1);
	else if (ft_strcmp(input[0], "cd") == 0)
		return (shell_cd(input), 1);
	else if (ft_strcmp(input[0], "export") == 0)
		return (shell_export(input), 1);
	else if (ft_strcmp(input[0], "unset") == 0)
		return (shell_unset(input), 1);
	else if (ft_strcmp(input[0], "exit") == 0)
		return (shell_exit(input), 1);
	return (0);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	i;

	i = 0;
	while (s[i] && i < n)
		i++;
	dup = (char *)malloc(sizeof(char) * (i + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
