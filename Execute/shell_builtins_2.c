
#include "minishell.h"

int shell_export(char **av) {
    char **env;
    char *name;
    char *value;
    int i;

    if (!av[1]) {
        env = *get_env();
        while (env && *env) {
            write(STDOUT_FILENO, *env, ft_strlen(*env));
            write(STDOUT_FILENO, "\n", 1);
            env++;
        }
        return (0);
    }
    i = 1;
    while (av[i]) {
        char *eq_pos = ft_strchr(av[i], '=');
        if (!eq_pos) {
            write(STDERR_FILENO, "export: invalid argument\n", 25);
            i++;
            continue;
        }
        name = ft_substr(av[i], 0, eq_pos - av[i]);
        value = ft_strdup(eq_pos + 1);
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
        if (!env || !*env) {
            char *new_entry = ft_strjoin(name, "=");
            char *final_entry = ft_strjoin(new_entry, value);
            free(new_entry);
            *env = final_entry;
            *(env + 1) = NULL;
        }
        free(name);
        free(value);
        i++;
    }
    return (0);
}