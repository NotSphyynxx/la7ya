#include "../minishell.h"

static char *collect_word(char *line, int *i)
{
    int start = *i;
    while (line[*i] && !ft_isspace(line[*i]) && !ft_strchr("|<>", line[*i]))
    {
        if (line[*i] == '\'' || line[*i] == '"')
        {
            char quote = line[(*i)++];
            while (line[*i] && line[*i] != quote)
                (*i)++;
            if (line[*i] == quote)
                (*i)++;
        }
        else
            (*i)++;
    }
    return ft_substr(line, start, *i - start); // includes quotes
}

void last_check(t_token **tokens, char *line, int *i)
{
    if (line[*i] == '\'' || line[*i] == '"')
        check_quote(tokens, line, i);
    else
    {
        char *word = collect_word(line, i);
        t_token *tok = new_token(word, WORD);
        add_token(tokens, tok);
        free(word);
    }
}