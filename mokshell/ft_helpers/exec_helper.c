/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:28:27 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/05/21 17:21:26 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_check(char **input, char **envp)
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

// Helper: split a single string on spaces, return array or NULL on malloc fail
static char **split_on_spaces(const char *s)
{
    char    **parts;
    int     n;

    parts = ft_split(s, ' ');
    if (!parts)
        return (NULL);
    // remove any empty entries
    n = 0;
    while (parts[n])
    {
        if (parts[n][0] == '\0')
        {
            ft_free_str_array(parts);
            return (NULL);
        }
        n++;
    }
    return (parts);
}
// Helper: count number of words in a string (split by spaces)
static int ft_count_words(const char *s, char c)
{
    int count = 0;
    int in_word = 0;

    while (*s)
    {
        if (*s != c && !in_word)
        {
            in_word = 1;
            count++;
        }
        else if (*s == c)
            in_word = 0;
        s++;
    }
    return (count);
}


static int is_assignment(const char *s)
{
    int i = 0;
    while (s[i] && s[i] != ' ')
    {
        if (s[i] == '=')
            return (1);
        i++;
    }
    return (0);
}

char **tokens_to_cmd(t_token *start, t_token *end)
{
    int     count = 0;
    t_token *t = start;
    char    **cmd;
    int     i = 0;

    // 1️⃣ Count how many argv slots we'll need
    while (t && t != end)
    {
        if (t->type == WORD || t->type == ENV_VAR)
        {
            char *clean = t->value;
            if (!t->was_single && !t->was_double)
                while (*clean == ' ')
                    clean++;
            if (*clean == '\0')
            {
                t = t->next;
                continue;
            }
            if (!t->was_single && !t->was_double && !is_assignment(clean) && ft_strchr(clean, ' '))
                count += ft_count_words(clean, ' '); // custom word-count function
            else
                count++;
        }
        else if (t->type == REDIR_OUT || t->type == REDIR_APPEND
              || t->type == REDIR_IN  || t->type == HEREDOC)
            t = t->next;
        t = t->next;
    }

    if (count == 0)
        return (NULL);

    cmd = malloc(sizeof(char *) * (count + 1));
    if (!cmd)
        return (NULL);

    // 2️⃣ Build argv
    t = start;
    while (t && t != end)
    {
        if (t->type == WORD || t->type == ENV_VAR)
        {
            char *clean = t->value;
            if (!t->was_single && !t->was_double)
                while (*clean == ' ')
                    clean++;
            if (*clean == '\0')
            {
                t = t->next;
                continue;
            }
            if (!t->was_single && !t->was_double && !is_assignment(clean) && ft_strchr(clean, ' '))
            {
                char **parts = ft_split(clean, ' ');
                if (parts)
                {
                    for (int j = 0; parts[j]; j++)
                        cmd[i++] = ft_strdup(parts[j]);
                    ft_free_str_array(parts);
                }
            }
            else
                cmd[i++] = ft_strdup(clean);
        }
        else if (t->type == REDIR_OUT || t->type == REDIR_APPEND
              || t->type == REDIR_IN  || t->type == HEREDOC)
            t = t->next;
        t = t->next;
    }
    cmd[i] = NULL;

    if (i == 0)
    {
        free(cmd);
        return (NULL);
    }

    return (cmd);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t 	i;

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
