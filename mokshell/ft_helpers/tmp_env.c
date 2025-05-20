#include "../minishell.h"

char ***get_env(void) {
    static char **env = NULL;
    return (&env);
}

char *get_env_value(char *key) {
    char **env;
    int i;
    int len;

    env = *get_env();
    len = ft_strlen(key);
    i = 0;
    while (env && env[i]) {
        if (!ft_strncmp(env[i], key, len) && env[i][len] == '=') {
            return (env[i] + len + 1);
        }
        i++;
    }
    return (NULL);
}

t_exp	**get_exp_list(void)
{
	static t_exp	*exp_list = NULL;
	return (&exp_list);
}

char	**init_env(char **envp)
{
	int	i;
	char **new_env;

	i = 0;
	while (envp[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
	{
		perror("malloc");
		return NULL;
	}
	i = 0;
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		i++;
	}
	new_env[i] = NULL;
	return(new_env);
}
