
#include "minishell.h"

static void ft_free_str_array(char **array) {
    int i = 0;

    if (!array)
        return;

    while (array[i]) {
        free(array[i]);
        i++;
    }

    free(array);
}

static char *find_command_path(char *cmd)
{
	char *path_env;
	char **paths;
	char *full_path;
	int i;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		if (!full_path)
		{
			ft_free_str_array(paths);
			return (NULL);
		}
		full_path = ft_strjoin(full_path, cmd);
		if (!full_path)
		{
			ft_free_str_array(paths);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
		{
			ft_free_str_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_str_array(paths);
	return (NULL);
}

void	cmnd_check(char **input, char **envp)
{
	if (ft_strcmp(input[0], "echo") == 0)
		shell_echo(input);
	else if (ft_strcmp(input[0], "env") == 0)
		shell_env(input, envp);
	else if (ft_strcmp(input[0], "pwd") == 0)
		shell_pwd(input);
	else if (ft_strcmp(input[0], "cd") == 0)
		shell_cd(input);
	else if (ft_strcmp(input[0], "export") == 0)
		shell_export(input);
	else if (ft_strcmp(input[0], "unset") == 0)
		shell_unset(input);
	else if (ft_strcmp(input[0], "exit") == 0)
		shell_exit(input);
	else
		execute(input);
}

void	execute(char	**input)
{
	pid_t	child_pid;
	char		*path;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork error");
		return ;
	}
	if (child_pid == 0)
	{
		path = find_command_path(input[0]);
		if (!path)
		{
			write(STDERR_FILENO, "minishell: command not found\n", 29);
			exit(127);
		}
		if (execve(path, input, *get_env()) == -1)
		{
			perror("execve error");
            exit(1);
		}
		else
			waitpid(child_pid, NULL, 0);
	}
}

