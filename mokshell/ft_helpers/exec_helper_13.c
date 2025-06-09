/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper_13.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:59:03 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/08 16:31:13 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_line(void)
{
	static char	*line;

	return (&line);
}

int	is_token_assign_or_space(t_token *t, char *clean)
{
	if (!t->was_single && !t->was_double)
		while (*clean == ' ')
			clean++;
	if (!t->was_single && !t->was_double
		&& !is_assignment(clean) && ft_strchr(clean, ' '))
		return (ft_countword(clean, ' '));
	return (1);
}

void	handle_word(char ***result, char **str, int *i)
{
	int	len;

	len = 0;
	while ((*str)[len] && (*str)[len] != ' ')
		len++;
	(*result)[(*i)++] = word_dup(*str, len);
	*str += len;
}

void	init_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = ft_strdup("/");
	*get_pwd_storage() = cwd;
}

int	ft_is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}
