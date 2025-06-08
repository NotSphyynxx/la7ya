#include "../minishell.h"

void	*gc_malloc(size_t size, t_exec *exec)
{
	void		*ptr;
	t_gc_node	*new_node;

	
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	new_node = malloc(sizeof(t_gc_node));
	if (!new_node)
		return (free(ptr), NULL);
	new_node->ptr = ptr;
	new_node->next = exec->gc_head;
	exec->gc_head = new_node;
	return (ptr);
}

void	gc_clear(t_exec *exec, char **readed, t_token *tokens, char **input)
{
	t_gc_node *tmp;

	while (exec->gc_head)
	{
		tmp = exec->gc_head->next;
		if (exec->gc_head->ptr)
			free(exec->gc_head->ptr);
		free(exec->gc_head);
		exec->gc_head = tmp;
	}
	if (*readed)
		free(*readed);
	if (tokens)
		free_tokens(tokens);
	ft_free_str_array(input);
}

t_exp	*split_env_to_exp(char *env_entry)
{
	t_exp	*node;
	char	*eq_sign;

	node = malloc(sizeof(t_exp));
	if (!node)
		return (NULL);
	eq_sign = ft_strchr(env_entry, '=');
	if (eq_sign)
	{
		node->key = ft_substr(env_entry, 0, eq_sign - env_entry);
		node->value = ft_strdup(eq_sign + 1);
	}
	else
	{
		node->key = ft_strdup(env_entry);
		node->value = NULL;
	}
	node->next = NULL;
	return (node);
}
void	sync_env_var(char *key, char *val)
{
	char	*entry;

	if (!val)
		return ;
	entry = ft_strjoin(key, "=");
	entry = ft_strjoin(entry, val);
	adjust_env(entry, key);
	free(entry);
}

void	parse_export_arg(char *arg, char **key, char **val, int *append)
{
	char	*plus;
	char	*eq;

	*append = 0;
	plus = ft_strnstr(arg, "+=", ft_strlen(arg));
	if (plus)
	{
		*append = 1;
		*key    = ft_substr(arg, 0, plus - arg);
		*val    = ft_strdup(plus + 2);
	}
	else if ((eq = ft_strchr(arg, '=')))
	{
		*key = ft_substr(arg, 0, eq - arg);
		*val = ft_strdup(eq + 1);
	}
	else
	{
		*key = ft_strdup(arg);
		*val = NULL;
	}
}
