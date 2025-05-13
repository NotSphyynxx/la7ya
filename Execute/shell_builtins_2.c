#include "minishell.h"

static	void	add_to_env(char **env, char *str)
{
	int i;

    i = 0;
    while(env && env[i])
    {
        i++;
    }
    char **new_env = malloc(sizeof(char *) * (i + 2));
    if (!new_env)
        return ;
    i = 0;
    while(env[i])
    {
        new_env[i] = env[i];
        i++;
    }
    new_env[i] = str;
    i++;
    new_env[i] = NULL;
    *get_env() = new_env;
}


int shell_export(char **av) {
    char **env;
    char *name;
    char *value;
    int i;

    if (!av[1]) {
        env = *get_env();
        while (env && *env) {
            write(STDOUT_FILENO, "declare -x ", 12);
            write(STDOUT_FILENO, *env, ft_strlen(*env));
            write(STDOUT_FILENO, "\n", 1);
            env++;
        }
        return (0);
    }
    i = 1;
    while (av[i]) {
        char *eq_pos = ft_strchr(av[i], '=');
        if (eq_pos)
        {
            name = ft_substr(av[i], 0, eq_pos - av[i]);
            value = ft_strdup(eq_pos + 1);
        }
        else
        {
            name = ft_strdup(av[i]);
            value = ft_strdup("");
        }
        char *name_ptr = name;
        while (*name_ptr) {
            if (!ft_isalnum(*name_ptr) && *name_ptr != '_') {
                write(STDERR_FILENO, "export: invalid name\n", 22);
                free(name);
                free(value);
                name = NULL;
                value = NULL;
                break;
            }
            name_ptr++;
        }
        if (!name || !value) {
            i++;
            continue;
        }
        char **env = *get_env();
        while (env && *env) {
            if (!ft_strncmp(*env, name, ft_strlen(name)) && (*env)[ft_strlen(name)] == '=') {
                *env = ft_strjoin(name, "=");
                char *new_entry = ft_strjoin(*env, value);
                free(*env);
                *env = new_entry;
                break;
            }
            env++;
        }
        if (!env || !*env)
		{
            env = *get_env();
            if (!env)
            {
                perror("malloc");
                exit (1);
            }
			char *final_entry;
			char *new_entry;
            if (eq_pos)
            {
                if (ft_strcmp(value, "") == 0)
                {
                    new_entry = ft_strjoin(name, "=""");
                    add_to_env(*get_env(), new_entry);
                }
                else
				{
					new_entry = ft_strjoin(name, "=");
					final_entry = ft_strjoin(new_entry, value);
					free(new_entry);
					add_to_env(*get_env(), final_entry);
				}
            }
			else if (!eq_pos)
			{
				printf("%s\n", name);
				add_to_env(*get_env(), name);
			}
			env = *get_env();
			while (env && *env) {
            write(STDOUT_FILENO, "declare -x ", 12);
            write(STDOUT_FILENO, *env, ft_strlen(*env));
            write(STDOUT_FILENO, "\n", 1);
            env++;
        }
        }
        free(name);
        free(value);
        i++;
    }
    return (0);
}

