
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
	else if (ft_strcmp(input[0], "export") == 0)
		shell_export(input);
	else if (ft_strcmp(input[0], "unset") == 0)
		shell_unset(input);
	else if (ft_strcmp(input[0], "exit") == 0)
		shell_exit(input);
}
