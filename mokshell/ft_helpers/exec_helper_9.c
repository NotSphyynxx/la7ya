#include "../minishell.h"

void	add_exp_back(t_exp **lst, t_exp *new)
{
	t_exp *tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int check_file_token(t_token *file_tok)
{
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
    return (0);
}

static int word_count(char *str)
{
    int count = 0;
    int in_word = 0;

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

static char *word_dup(char *start, int len)
{
    char *word;
    int i;

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

char **split_on_spaces(char *str)
{
    char **result;
    int i = 0;
    int len = 0;

    int words = word_count(str);
    result = malloc(sizeof(char *) * (words + 1));
    if (!result)
        return (NULL);
    while (*str)
    {
        if (*str != ' ')
        {
            len = 0;
            while (str[len] && str[len] != ' ')
                len++;
            result[i++] = word_dup(str, len);
            str += len;
        }
        else
            str++;
    }
    result[i] = NULL;
    return (result);
}
