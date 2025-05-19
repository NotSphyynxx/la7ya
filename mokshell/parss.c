
#include "minishell.h"


t_token *parss(char *line, t_parss *envr)
{
    t_token *tokens = NULL;
    int i = 0;
    while (line[i])
    {
        if (ft_isspace(line[i]))
        {
            i++;
            continue;
        }
        if (line[i] == '|')
        {
            if (line[i + 1] == '|') {
                printf("Syntax error: unexpected token '||'\n");
                return NULL;
            }
            add_token(&tokens, new_token(ft_strdup("|"), PIPE));
            i++;
        }
        else if (line[i] == '>' || line[i] == '<')
        {
            if (line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '>')
            {
                printf("Syntax error: unexpected '>>>'\n");
                return NULL;
            }
            else if (line[i] == '>' && line[i + 1] == '>')
            {
                add_token(&tokens, new_token(ft_strdup(">>"), REDIR_APPEND));
                i += 2;
            }
            else if (line[i] == '<' && line[i + 1] == '<')
            {
                add_token(&tokens, new_token(ft_strdup("<<"), HEREDOC));
                i += 2;
            }
            else
            {
                char op[2] = {line[i], '\0'};
                t_type type;
                if (line[i] == '>')
                    type = REDIR_OUT;
                else
                    type = REDIR_IN;
                add_token(&tokens, new_token(ft_strdup(op), type));
                i++;
            }
        }
        else if (line[i] == '\'' || line[i] == '"')
        {
            char quote = line[i++];
            int start = i;
            while (line[i] && line[i] != quote)
                i++;
            if (!line[i])
            {
                printf("Syntax error: unclosed quote\n");
                return NULL;
            }
            char *quoted = ft_substr(line, start, i - start);
            add_token(&tokens, new_token(quoted, WORD));
			tokens->was_single = 0;
            if (quote == '\'')
                tokens->was_single = 1;
            else
                tokens->was_double = 1;
            i++; // Skip closing quote
        }
        else
        {
            int start = i;
            while (line[i] && !ft_isspace(line[i]) && !ft_strchr("|<>\"\'", line[i]))
                i++;
            char *word = ft_substr(line, start, i - start);
            add_token(&tokens, new_token(word, WORD));
        }
    }

    if (check_syntax(tokens))
    {
        printf("Invalid syntax.\n");
        return NULL;
    }
    expand(tokens, envr->env);
	return (tokens);
}