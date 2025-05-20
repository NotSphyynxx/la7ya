
#include "minishell.h"

#include "minishell.h"


static char *strjoin(const char *s1, const char *s2)
{
    if (!s1 || !s2)
        return NULL;

    size_t len1 = ft_strlen(s1);
    size_t len2 = ft_strlen(s2);

    char *res = malloc(len1 + len2 + 1);
    if (!res)
        return NULL;

    ft_strcpy(res, s1);
    ft_strcat(res, s2);

    return res;
}

char *get_env2_value(const char *name)
{
    char **env = *get_env();
    int i = 0;
    while (env[i])
    {
        char *equal = ft_strchr(env[i], '=');
        if (equal)
        {
            int len = equal - env[i];
            if (ft_strncmp(name, env[i], len) == 0 && ft_strlen(name) == (size_t)len)
                return equal + 1;
        }
        i++;
    }
    return "";
}

char *expand_variable(char *line)
{
    int i = 0;
    int start = 0;
    char *result = ft_strdup("");

    while (line[i])
    {
        if (line[i] == '$')
        {
            // Append text before $
            char *before = ft_substr(line, start, i - start);
            char *tmp = result;
            result = ft_strjoin(tmp, before);
            free(tmp);
            free(before);

            i++; // skip $
            int var_start = i;
            while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
                i++;
            char *var_name = ft_substr(line, var_start, i - var_start);
            char *val = ft_strdup(get_env2_value(var_name));

            tmp = result;
            result = ft_strjoin(tmp, val);
            free(tmp);
            free(val);
            free(var_name);

            start = i; // start of next chunk
        }
        else
            i++;
    }

    // Append the rest of the line
    if (start < i)
    {
        char *remaining = ft_substr(line, start, i - start);
        char *tmp = result;
        result = ft_strjoin(tmp, remaining);
        free(tmp);
        free(remaining);
    }
    return result;
}

void expand(t_token *tokens)
{
    t_token *curr = tokens;
    while (curr)
    {
        printf("  [expand] token='%s' will%s expand\n",
               curr->value,
               (!curr->was_single && ft_strchr(curr->value, '$')) ? "" : " not");
        if (curr->type == WORD && !curr->was_single && ft_strchr(curr->value, '$'))
        {
            char *expanded = expand_variable(curr->value);
            free(curr->value);
            curr->value = expanded;
            printf("             -> '%s'\n", curr->value);
        }
        curr = curr->next;
    }
}
