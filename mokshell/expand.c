
#include "minishell.h"

void expand(t_token *tokens, char **env)
{
    t_token *curr = tokens;
    int i = 0;

    while (curr)
    {
        printf("now %d\n", curr->was_single);
        if (curr->type == WORD && !curr->was_single && curr->value[0] == '$')
        {
            i++;
            char *var_name = curr->value + 1; // Skip the '$'
            int i = 0;
            int found = 0;

            while (env[i])
            {
                char *equal = ft_strchr(env[i], '=');
                if (equal)
                {
                    int var_len = equal - env[i];
                    if (ft_strncmp(var_name, env[i], var_len) == 0 &&
                        (int)ft_strlen(var_name) == var_len)
                    {
                        free(curr->value);
                        curr->value = ft_strdup(equal + 1); // value after '='
                        found = 1;
                        break;
                    }
                }
                i++;
            }

            if (!found)
            {
                free(curr->value);
                curr->value = ft_strdup(""); // Replace with empty string if not found
            }
        }
        curr = curr->next;
    }
    curr = tokens;
    while (curr)
    {
        printf("Expanded Token: %s\n", curr->value);
        curr = curr->next;
    }
}