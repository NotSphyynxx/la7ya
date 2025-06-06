
#include "../minishell.h"

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

// Replace variables in a string line
char *expand_variable(char *line, int *flag)
{
    int i = 0;
    int start = 0;
    char *result = ft_strdup("");
    char *tmp;

    while (line[i])
    {
        if (line[i] == '$')
        {
            // Append text before $
            char *before = ft_substr(line, start, i - start);
            tmp = result;
            result = ft_strjoin(tmp, before);
            free(tmp);
            free(before);
            i++; // skip $

            if (line[i] == '?')
            {
                // Special case: exit status
                char *exit_status_str = ft_itoa(get_shell()->exit_status);
                tmp = result;
                result = ft_strjoin(tmp, exit_status_str);
                free(tmp);
                free(exit_status_str);
                i++; // skip '?'
            }
            else if (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
            {
                // Regular variable
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
                *flag = 1;
            }
            else
            {
                // Just a lone '$' — copy it as-is
                tmp = result;
                result = ft_strjoin(tmp, "$");
                free(tmp);
            }
            start = i;
        }
        else
            i++;
    }
    // Append remaining text after last $
    if (start < i)
    {
        char *remaining = ft_substr(line, start, i - start);
        tmp = result;
        result = ft_strjoin(tmp, remaining);
        free(tmp);
        free(remaining);
    }
    return result;
}

// Expand variables in tokens and detect ambiguous redirections
void expand(t_token *tokens)
{
    t_token *curr = tokens;
    int flag = 0;

    // 1️⃣ Variable expansion pass
    while (curr)
    {
        if (curr->type == WORD && !curr->was_single && ft_strchr(curr->value, '$'))
        {
            char *expanded = expand_variable(curr->value, &flag);
            free(curr->value);
            curr->value = expanded;
        }
        curr = curr->next;
    }

    // 2️⃣ Ambiguous redirection detection pass
    curr = tokens;  // 🔥 Reset curr before this second pass
    while (curr)
    {
        if (curr->type == REDIR_IN || curr->type == REDIR_OUT ||
            curr->type == REDIR_APPEND || curr->type == HEREDOC)
        {
            if (!curr->next || !curr->next->value || ft_strlen(curr->next->value) == 0
                || wf_name(curr->next->value, flag) == 1)
            {
                if (curr->next)
                    curr->next->ambigious = 1;
            }
        }
        curr = curr->next;
    }
}

