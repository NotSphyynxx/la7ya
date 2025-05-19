
#include "minishell.h"

void expand(t_token *tokens, char **env)
{
    if (!tokens || !tokens->value)
        return;
    char *envar = (char *)tokens->value;
    t_token *curr = tokens;
    int i = 0;
    if (envar[0] == '$')
    {
        if (envar[1] == '\0')
            return;

        i = 0;
        while (env[i])
        {
            char *equal = ft_strchr(env[i], '=');
            if (equal)
            {
                int var_len = equal - env[i];
                if (ft_strncmp(curr->value + 1, env[i], var_len) == 0 &&
                    (int)ft_strlen(curr->value + 1) == var_len)
                {
                    free(tokens->value);
                    tokens->value = ft_substr(env[i], var_len + 1,
                                                ft_strlen(env[i]) - var_len - 1);
                    break;
                }
            }
            i++;
        }
    }
}
