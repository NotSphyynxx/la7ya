
#include "includes/minishell.h"

void expand(t_token *tokens, char **env)
{
    if (!tokens || !tokens->content)
        return;
    char *envar = (char *)tokens->content;
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
                if (ft_strncmp(curr->content + 1, env[i], var_len) == 0 &&
                    (int)ft_strlen(curr->content + 1) == var_len)
                {
                    free(tokens->content);
                    tokens->content = ft_substr(env[i], var_len + 1,
                                                ft_strlen(env[i]) - var_len - 1);
                    printf("%s\n", tokens->content);
                    break;
                }
            }
            i++;
        }
    }
}
