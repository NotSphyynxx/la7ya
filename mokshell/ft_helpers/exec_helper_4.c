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
	int		i;
	int		eq_flag;
	char	*tmp;
	char	*var;

	i = 0;
	eq_flag =0;
	tmp = ft_strjoin(name, "=");
	var = ft_strjoin(tmp, value);
	free(tmp);
	while (av[i])
	{
		if (av[i] == '=')
			eq_flag = 1;
		i++;
	}
	if (eq_flag)
	{
		if (adjust_env(var, name) == 1)
			free(var);
	}
	else
	{
		free(var);
	}
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
		new_env[i] = env[i];
		i++;
	}
	new_env[i++] = ft_strdup(var);
	new_env[i] = NULL;
	ft_free_str_array(*get_env());
	*get_env() = new_env;
	return (0);
}

int	exist_check(char *env, char *name)
{
	char	**mot;

	mot = ft_split(env, '=');
	if(!mot)
	{
		perror("malloc");
		return (0);
	}
	for(int i = 0; mot[i]; i++)
	{
		printf("mot[%d] = %s\n", i, mot[i]);
	}
	if (ft_strcmp(mot[0], name) == 0)
	{
		ft_free_str_array(mot);
		return (1);
	}
	ft_free_str_array(mot);
	return (0);
}
