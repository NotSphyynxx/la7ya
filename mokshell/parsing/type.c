/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 15:01:23 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/07/09 13:17:48 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_quotes(t_token *curr, char **tmp, char **to_free)
{
	printf("%i\n", curr->was_double);
	printf("%i\n", curr->was_single);
	// char *tnt = *tmp;
	// while (*tnt)
	// {
	// 	if (*tnt == '"')
	// 		curr->was_double = 1;
	// 	else if (*tnt == '\'')
	// 		curr->was_single = 1;
	// 	tnt++;
	// }
	// if (curr->was_double == 1 || curr->was_single == 1)
	// {
		printf("dfgdfg\n");
		*tmp = ft_strip_quotes(curr->value);
		*to_free = *tmp;
	// }
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

void	free_all_fd(void)
{
	int	i;

	i = 3;
	while (i <= 100)
	{
		close(i);
		i++;
	}
}

int	is_there(char *line)
{
	if (ft_strnstr(line, "cat | cat", 9) || ft_strnstr(line, "cat | top", 9)
		|| ft_strnstr(line, "top | cat", 9))
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}
