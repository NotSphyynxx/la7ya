#include "../minishell.h"

void	add_or_append_exp(char *plus_eq_pos, t_exp *existing, char **value)
{
	if (plus_eq_pos)
	{
		char *tmp = existing->value;
		if (existing->value)
			existing->value = ft_strjoin(existing->value, *value);
		else
			existing->value = ft_strdup(*value);
		free(tmp);
		free(*value);
	}
	else
	{
		if (existing->value)
			free(existing->value);
		existing->value = *value;
	}
}

void	add_or_append_check(char *av, char **key, char **value, char *plus_eq_pos)
{
	char	*eq_pos;

	if (plus_eq_pos)
	{
		*key = ft_substr(av, 0, plus_eq_pos - av);
		*value = ft_strdup(plus_eq_pos + 2);
	}
	else
	{
		eq_pos = ft_strchr(av, '=');
		if (eq_pos)
		{
			*key = ft_substr(av, 0, eq_pos - av);
			*value = ft_strdup(eq_pos + 1);
		}
		else
		{
			*key = ft_strdup(av);
			*value = NULL;
		}
	}
}

void	export_variable(char *av, t_exp *existing)
{
	char	*plus_eq_pos;
	char	*key;
	char	*value;

	plus_eq_pos = ft_strnstr(av, "+=", ft_strlen(av));
	add_or_append_check(av, &key, &value, plus_eq_pos);
	if (!check_valid_key(key))
	{
		error_export(&key, &value);
		return ;
	}
	existing = find_exp(*get_exp_list(), key);
	if (existing)
	{
		add_or_append_exp(plus_eq_pos, existing, &value);
		add_to_env(av, key, existing->value);
	}
	else
	{
		create_and_fill(plus_eq_pos, &value, key);
		add_to_env(av, key, value);
		if (plus_eq_pos)
			free(value);
	}
	free(key);
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

int	shell_export(char **av)
{
	int i;
	t_exp *existing;

	i = 1;
	existing = NULL;
	if (!av[1])
	{
		printf_export_list();
		return (0);
	}
	while (av[i])
	{
		if (ft_strlen(av[i]) > 0)
			export_variable(av[i], existing);
		i++;
	}
	return (0);
}
