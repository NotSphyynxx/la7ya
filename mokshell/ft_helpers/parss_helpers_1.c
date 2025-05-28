#include "../minishell.h"

int check_all(t_token **tokens, char *line, int *i)
{
    while (line[*i])
    {
        if (ft_isspace(line[*i]))
        {
            (*i)++;
            continue;
        }
        if (line[*i] == '|')
        {
            if (!check_pipe(tokens, line, i))
                return (0);
        }
        else if (line[*i] == '>' || line[*i] == '<')
        {
            if (!check_heredoc(tokens, line, i))
                return (0);
        }
        else
            if (last_check(tokens, line, i) == 1)
                return 0;
    }
    return 1;
}

int    check_pipe(t_token **tokens, char *line, int *i)
{
    if (line[*i + 1] == '|')
    {
        printf("Syntax error: unexpected token '||'\n");
        return 0;
    }
    add_token(tokens, new_token(ft_strdup("|"), PIPE));
    (*i)++;
    return 1;
}
int check_heredoc(t_token **tokens, char *line, int *i)
{
    if (line[*i] == '>' && line[*i + 1] == '>' && line[*i + 2] == '>')
    {
        printf("Syntax error: unexpected '>>>'\n");
        return 0;
    }
    else if (line[*i] == '>' && line[*i + 1] == '>')
    {
        add_token(tokens, new_token(ft_strdup(">>"), REDIR_APPEND));
        (*i) += 2;
    }
    else if (line[*i] == '<' && line[*i + 1] == '<')
    {
        add_token(tokens, new_token(ft_strdup("<<"), HEREDOC));
        (*i) += 2;
    }
    else
    {
        char op[2] = {line[*i], '\0'};
        t_type type;
        if (line[*i] == '>')
            type = REDIR_OUT;
        else
            type = REDIR_IN;
        add_token(tokens, new_token(ft_strdup(op), type));
        (*i)++;
    }
    return 1;
}
int check_quote(t_token **tokens, char *line, int *i)
{
    char quote = line[(*i)++];
    int start = *i;

    while (line[*i] && line[*i] != quote)
        (*i)++;

    if (!line[*i])
    {
        printf("Syntax error: unclosed quote\n");
        return 0;
    }
    // Include the quotes when storing the value
    int full_len = *i - start + 2; // +2 for both quotes
    char *full_quoted = ft_substr(line, start - 1, full_len);

    t_token *new_tok = new_token(full_quoted, WORD);
    if (quote == '\'')
        new_tok->was_single = 1;
    else
        new_tok->was_double = 1;
    add_token(tokens, new_tok);
    free(full_quoted);
    (*i)++; // skip closing quote
    return 1;
}

int check_syntax(t_token *tokens)
{
    t_token *current = tokens;

    if (current && current->type == PIPE)
    {
        printf("Syntax error: unexpected '|' \n");
        return 1;
    }
    while (current)
    {
        if (current->type == PIPE && current->next && current->next->type == PIPE)
        {
            printf("Syntax error: unexpected '||' \n");
            return 1;
        }
        if (current->type == PIPE && current->next == NULL)
        {
            printf("Syntax error: unexpected '|' \n");
            return 1;
        }
        if ((current->type == REDIR_IN || current->type == REDIR_OUT ||
            current->type == REDIR_APPEND || current->type == HEREDOC)
            && (current->next == NULL || current->next->type != WORD))
        {
            printf("Syntax error: missing file after redirection\n");
            return 1;
        }
        if (current && current->type == WORD 
            && current->next  && current->next->type == PIPE 
            && current->next->next && current->next->next->type == PIPE)
        {
            printf("Syntax error: missing file after redirection\n");
            return 1;
        }
        if (current && current->type == WORD && current->next  
            && current->next->type == DOUBLE_QUOTE1)
        {
            printf("Error: missing closing \"\n");
            return 1;
        }
        if (current && current->type == WORD && current->next  
            && current->next->type == SINGLE_QUOTE1)
        {
            printf("Error: missing closing \'\n");
            return 1;
        }
        current = current->next;
    }
    return 0;
}
