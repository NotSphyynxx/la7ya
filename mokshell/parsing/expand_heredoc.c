
#include "../minishell.h"

char	*get_env2_val(const char *name)
{
	char	**env;
	int		i;
	int		len;
	char	*equal;

	env = *get_env();
	i = 0;
	while (env[i])
	{
		equal = ft_strchr(env[i], '=');
		if (equal)
		{
			len = equal - env[i];
			if (ft_strncmp(name, env[i], len) == 0 && ft_strlen(name) == (size_t)len)
				return equal + 1;
		}
		i++;
	}
	return "";
}

void	expand_heredoc(t_token *tokens)
{
	t_token *curr;
	char *expanded;

	curr = tokens;
	expanded = expand_var(curr->value);
	while (curr)
	{
		if (curr->type == REDIR_IN || curr->type == REDIR_OUT ||
			curr->type == REDIR_APPEND || curr->type == HEREDOC)
		{
			if (!curr->next || !curr->next->value || ft_strlen(curr->next->value) == 0)
			{
				if (curr->next)
					curr->next->ambigious = 1;
			}
		}
		curr = curr->next;
	}
}
