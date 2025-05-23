#include "../minishell.h"

int	ft_isalpha(int ch)
{
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
	{
		return (1);
	}
	return (0);
}

void	add_to_env(char *av, char *name, char *value)
{
	char	*new_entry;
	char	*tmp;
	char	*existing_val;
	char	*final_value;

	if (!has_equal_sign(av))
		return ;
	final_value = value;
	if (is_append_export(av))
	{
		existing_val = get_env_value(name);
		if (existing_val)
			final_value = ft_strjoin(existing_val, value);
		else
			final_value = ft_strdup(value);
	}
	new_entry = ft_strjoin(name, "=");
	tmp = new_entry;
	new_entry = ft_strjoin(new_entry, final_value);
	free(tmp);
	if (adjust_env(new_entry, name) == 1)
		free(new_entry);
	else
		free(new_entry);
	if (is_append_export(av))
		free(final_value);
}

int	adjust_env(char *var, char *name)
{
	char	**env;
	int		i;
	char	*tmp;

	i = 0;
	env = *get_env();
	while (env[i])
	{
		if (exist_check(env[i], name))
		{
			free(env[i]);
			env[i] = ft_strdup(var);
			return (1);
		}
		i++;
	}
	if (!env || !env[i])
	{
		if(realloc_env(var) == 1)
			return (1);
	}
	return (0);
}

int	realloc_env(char *var)
{
	char	**env;
	int		i;
	char	**new_env;

	env = *get_env();
	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
	{
		write(STDERR_FILENO, "malloc\n", 8);
		return (1);
	}
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i++] = ft_strdup(var);
	new_env[i] = NULL;
	ft_free_str_array(*get_env());
	*get_env() = new_env;
	return (0);
}

int	exist_check(char *env_entry, char *name)
{
	int	len;

	len = ft_strlen(name);
	if (ft_strncmp(env_entry, name, len) == 0 && env_entry[len] == '=')
		return (1);
	return (0);
}
