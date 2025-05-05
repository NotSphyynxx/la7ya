/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parss.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:49:53 by bael-bad          #+#    #+#             */
/*   Updated: 2025/05/05 17:16:36 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void parss()
{
	char	*line;
	char	**buffer;
	t_token	*tokens;
	int		i;
	int		j;

	i = 0;
	j = 0;
	// int k = 1;
	tokens = NULL;
	line = readline("Minishell:");
	if (!line)
		exit(1);
	if (*line)
		add_history(line);
	buffer = ft_split(line, ' ');
	while (buffer[i])
	{
		// while (buffer[j])
		// {
		// 	i = 0;
		// 	if (buffer[j][i] == '\'')
		// 	{
		// 		k++;
		// 		i++;
		// 	}
		// 	j++;
		// }
		if (ft_strcmp(buffer[i], "<") == 0)
			add_token(&tokens, new_token(buffer[i], REDIR_IN));
		else if (ft_strcmp(buffer[i], ">") == 0)
			add_token(&tokens, new_token(buffer[i], REDIR_OUT));
		else if (buffer[i][0] == '>' && buffer[i][1] == '>' && buffer[i][2] == '>')
		{
			printf("Syntax error: unexpected '>>>'\n");
			return ;
		}
		else if (buffer[i][0] == '|' && buffer[i][1] == '|')
		{
            printf("Syntax error: unexpected '||' \n");
			printf("Invalid syntax.\n");
            return ;
		}
		else if (ft_strcmp(buffer[i], "|") == 0)
			add_token(&tokens, new_token(buffer[i], PIPE));
		else if (ft_strcmp(buffer[i], ">>") == 0)
			add_token(&tokens, new_token(buffer[i], REDIR_APPEND));
		else if (ft_strcmp(buffer[i], "<<") == 0)
			add_token(&tokens, new_token(buffer[i], HEREDOC));
		else if (buffer[i][0] == '$')
			add_token(&tokens, new_token(buffer[i], ENV_VAR));
		// else if (buffer[i][0] == '\'' && buffer[i][ft_strlen(buffer[i]) - 1] == '\'')
		// 	add_token(&tokens, new_token(buffer[i], SINGLE_QUOTE2));
		// else if (buffer[i][0] == '"' && buffer[i][ft_strlen(buffer[i]) - 1] == '"')
		// 	add_token(&tokens, new_token(buffer[i], DOUBLE_QUOTE2));
		// else if (buffer[i][0] == '\'' && buffer[i][ft_strlen(buffer[i]) - 1] != '\'')
		// 	add_token(&tokens, new_token(buffer[i], SINGLE_QUOTE1));
		// else if (buffer[i][0] == '"' && buffer[i][ft_strlen(buffer[i]) - 1] != '"')
		// 	add_token(&tokens, new_token(buffer[i], DOUBLE_QUOTE1));
		else
			add_token(&tokens, new_token(buffer[i], WORD));
		i++;
	}
	// if (k % 2 == 0)
	// {
	// 	printf("error");
	// 	exit(0);
	// }
	if (check_syntax(tokens) != 0)
	{
		printf("Invalid syntax.\n");
		return ;
	}
	t_token	*temp = tokens;
	while (temp)
	{
		printf("Token: type=%s, value=%s\n", type_to_string(temp->type), temp->value);
        temp = temp->next;
	}
}