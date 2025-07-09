/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:35:54 by bael-bad          #+#    #+#             */
/*   Updated: 2025/07/09 11:07:12 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	token_space(t_token **tokens, char *line, int *i)
{
	int		start;
	t_token *tok;
	char	*spaces;
	int		len;

	start = *i;
	while (line[*i] == ' ')
		(*i)++;
	len = *i - start;
	if (len > 0)
	{
		spaces = ft_substr(line, start, len);
		if (!spaces)
			return ;
		tok = new_token(spaces, T_SPACE);
		add_token(tokens, tok);
	}
}


