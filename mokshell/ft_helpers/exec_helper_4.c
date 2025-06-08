#include "../minishell.h"

int	ft_isalpha(int ch)
{
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
	{
		return (1);
	}
	return (0);
}

static char	*create_env_entry(char *name, char *value)
{
	char	*tmp;
	char	*new_entry;

	tmp = ft_strjoin(name, "=");
	new_entry = ft_strjoin(tmp, value);
	free(tmp);
	return (new_entry);
}

void	add_to_env(char *av, char *name, char *value)
{
	char	*new_entry;
	char	*tmp;
	char	*final_value;

	if (!has_equal_sign(av))
		return ;
	final_value = ft_strdup(value);
	new_entry = ft_strjoin(name, "=");
	tmp = new_entry;
	new_entry = ft_strjoin(new_entry, final_value);
	free(tmp);
	if (adjust_env(new_entry, name) == 1)
		free(new_entry);
	else
		free(new_entry);
	free(final_value);
}

char	**copy_env_and_add(char **env, char *var)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i++] = ft_strdup(var);
	new_env[i] = NULL;
	return (new_env);
}

int	realloc_env(char *var)
{
	char	**env;
	char	**new_env;

	env = *get_env();
	new_env = copy_env_and_add(env, var);
	if (!new_env)
	{
		write(STDERR_FILENO, "malloc\n", 8);
		set_exit_status(2);
		return (1);
	}
	ft_free_str_array(*get_env());
	*get_env() = new_env;
	return (0);
}
