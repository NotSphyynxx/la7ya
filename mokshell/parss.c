
#include "minishell.h"

char *strip_quotes(char *str)
{
    size_t len = ft_strlen(str);
    char *result = malloc(len + 1);
    size_t i = 0, j = 0;

    if (!result)
        return NULL;
    while (str[i])
    {
        if (str[i] == '\'' || str[i] == '"')
        {
            char quote = str[i++];
            while (str[i] && str[i] != quote)
                result[j++] = str[i++];
            if (str[i] == quote)
                i++;
        }
        else
        {
            result[j++] = str[i++];
        }
    }
    result[j] = '\0';
    return result;
}

static void remove_quotes_tokens(t_token *tokens)
{
    while (tokens)
    {
        if (tokens->type == WORD)
        {
            char *stripped = strip_quotes(tokens->value);
            free(tokens->value);
            tokens->value = stripped;
        }
        tokens = tokens->next;
    }
}

t_token *parss(char *line)
{
    t_token *tokens = NULL;
    int i = 0;
    if (!check_all(&tokens, line, &i))
        return (NULL);
    
    if (check_syntax(tokens))
    {
        printf("Invalid syntax.\n");
        return NULL;
    }
    expand(tokens);
    remove_quotes_tokens(tokens);
    return (tokens);
}
