/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper_9.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:58:38 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/08 16:05:24 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_spaces(t_token *file_tok)
{
	int		i;
	int		j;
	char	*tmp;

	j = 0;
	i = 0;
	while (file_tok->value[j] == ' ')
		j++;
	i = ft_strlen(file_tok->value + j);
	tmp = file_tok->value;
	file_tok->value = malloc(sizeof(char) * (i + 1));
	if (!file_tok->value)
		return (-1);
	i = 0;
	while (tmp[j])
	{
		file_tok->value[i] = tmp[j];
		j++;
		i++;
	}
	file_tok->value[i] = '\0';
	free(tmp);
	return (0);
}

int	check_file_token(t_token *file_tok)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!file_tok || !file_tok->value || file_tok->value[0] == '\0')
	{
		write(STDERR_FILENO, "minishell: ambiguous redirect\n", 30);
		return (-1);
	}
	if (file_tok->ambigious)
	{
		write(STDERR_FILENO, "minishell: ambiguous redirect\n", 30);
		return (-1);
	}
	if (file_tok->value[0] == ' ')
	{
		if (skip_spaces(file_tok) == -1)
			return (-1);
	}
	return (0);
}

static int	word_count(char *str)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != ' ' && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*str == ' ')
			in_word = 0;
		str++;
	}
	return (count);
}

char	*word_dup(char *start, int len)
{
	char	*word;
	int		i;

	word = malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**split_on_spaces(char *str)
{
	char	**result;
	int		i;
	int		words;

	i = 0;
	words = word_count(str);
	result = malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	while (*str)
	{
		if (*str != ' ')
			handle_word(&result, &str, &i);
		else
			str++;
	}
	result[i] = NULL;
	return (result);
}
