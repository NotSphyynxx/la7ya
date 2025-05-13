
#include "minishell.h"

int shell_echo(char **av)
{
	int	i;
	int	new_line;
	char	**str;

	str = av;
	i = 1;
	new_line = 1;
	if (av[1] && av[1][0] == '-' && av[1][1] == 'n' && av[1][2] == '\0')
	{
		new_line = 0;
		i = 2;
	}
	while (av[i])
	{
		char *p = av[i];
		while (*p)
		{
			write(STDOUT_FILENO, p, 1);
			p++;
		}
		if (av[i + 1])
			write(STDOUT_FILENO, " ", 1);
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
			perror("cd");
	}
	else
	{
		if (chdir(args[1]) != 0)
			perror("cd");
	}
}
