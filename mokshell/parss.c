
#include "minishell.h"


t_token *parss(char *line, t_parss *envr)
{
    t_token *tokens = NULL;
    int i = 0;

    while (line[i])
    {
        // Skip spaces
        if (ft_isspace(line[i]))
        {
            i++;
            continue;
        }

        // Handle PIPE
        if (line[i] == '|')
        {
            if (line[i + 1] == '|') {
                printf("Syntax error: unexpected token '||'\n");
                return NULL;
            }
            add_token(&tokens, new_token(ft_strdup("|"), PIPE));
            i++;
        }
        // Handle Redirections
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
        // Handle Quoted Strings
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
            if (quote == '\'')
                tokens->was_single = 1;
            else
                tokens->was_double = 1;
			printf("the value == %s || the single count %d\n", tokens->value, tokens->was_single);
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

    // Debug print tokens
    // t_token *tmp = tokens;
    // while (tmp)
    // {
    //     printf("Token: type=%s, value=%s\n was_single = %d, was_double = %d\n", type_to_string(tmp->type), tmp->value, tokens->was_single, tokens->was_double);
    //     tmp = tmp->next;
    // }
    // printf("%s\n", tmp->value);

    // Handle expansion here if needed
	t_token *tmpp = tokens;
	while (tmpp)
	{
		printf("before expand--> %s\n", tmpp->value);
		tmpp = tmpp->next;
	}
	printf("%d\n", tokens->was_single);
    expand(tokens, envr->env);
	return (tokens);
}