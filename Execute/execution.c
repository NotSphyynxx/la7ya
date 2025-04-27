
#include "minishell.h"

void	execute(char **input, char **envp)
{
	if (ft_strcmp(input[0], "echo") == 0)
		shell_echo(input);
	else if (ft_strcmp(input[0], "env") == 0)
		shell_env(input, envp);
	else if (ft_strcmp(input[0], "pwd") == 0)
		shell_pwd(input);
	else if (ft_strcmp(input[0], "cd") == 0)
		shell_cd(input);
}