#include "minishell.h"

void	export_variable(char *av)
{
	char	*eq_pos;
	char	*key;
	char	*value;
	t_exp	*existing;

	eq_pos = ft_strchr(av, '=');
	if (eq_pos)
	{
		key = ft_substr(av, 0, eq_pos - av);
		value = ft_strdup(eq_pos + 1);
	}
	else
	{
		key = ft_strdup(av);
		value = NULL;
	}
	if (!check_valid_key(key))
	{
		write(2, "export: invalid identifier\n", 27);
		free(key);
		if (value)
			free(value);
		return ;
	}
	existing = find_exp(*get_exp_list(), key);
	if (existing)
	{
		if (existing->value)
			free(existing->value);
		existing->value = value;
	}
	else
	{
		add_exp_back(get_exp_list(), new_exp_node(key, value));
		return ;
	}
	if (!existing)
		return ;
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

void	init_export_list(void)
{
	char	**env;
	int		i;
	t_exp	*node;

	env = *get_env();
	i = 0;
	while (env && env[i])
	{
		node = split_env_to_exp(env[i]);
		add_exp_back(get_exp_list(), node);
		i++;
	}
}

int	shell_export(char **av)
{
	int i;

	i = 1;
	if (!av[1])
	{
		printf_export_list();
		return (0);
	}
	while (av[i])
	{
		export_variable(av[i]);
		i++;
	}
	return (0);
}

