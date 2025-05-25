
#include "minishell.h"

int shell_echo(char **av)
{
	int i = 1;
	int new_line = 1;

	while (av[i] && av[i][0] == '\0')
		i++;
	while (av[i] && av[i][0] == '-' && av[i][1] == 'n')
	{
		int j = 1;
		while (av[i][j] == 'n')
			j++;
		if (av[i][j] != '\0')
			break;
		new_line = 0;
		i++;
		while (av[i] && av[i][0] == '\0')
			i++;
	}
	while (av[i])
	{
		if (av[i][0] != '\0')
		{
			write(STDOUT_FILENO, av[i], ft_strlen(av[i]));
			if (av[i + 1])
				write(STDOUT_FILENO, " ", 1);
		}
		i++;
	}
	if (new_line)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}



int	shell_env(char **av,  char **envp)
{
	char	**env;

	if (av[1])
	{
		write(STDERR_FILENO, "env: too many arguments\n", 24);
		return (1);
	}
	env = envp;
	if (*env == NULL)
	{
		char *cd = getcwd(NULL, 0);
		write(STDOUT_FILENO, cd, ft_strlen(cd));
		write(STDOUT_FILENO, "\n", 1);
		write(STDOUT_FILENO, "SHLVL=1\n", 8);
		write(STDOUT_FILENO, "_=/usr/bin/env\n", 15);

	}
	while (*env)
	{
		write (STDOUT_FILENO, *env, ft_strlen(*env));
		write (STDOUT_FILENO, "\n", 1);
		env++;
	}
	return (0);
}

int	shell_pwd(char **av)
{
	char	*cwd;

	(void)av;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		write(STDERR_FILENO, "pwd: error getting directory\n", 29);
		return (1);
	}
	write(STDOUT_FILENO, cwd, ft_strlen(cwd));
	write(STDOUT_FILENO, "\n", 1);
	free(cwd);
	return (0);
}
void	shell_cd(char **args)
{
	char	*path;

	if (!args[1])
	{
		path = get_env_value("HOME");
		if (!path || chdir(path) != 0)
			write(STDERR_FILENO, "minishell: cd: PATH not set\n", 29);
	}
	else
	{
		if (chdir(args[1]) != 0)
			perror("cd");
	}
}
