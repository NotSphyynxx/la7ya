#include "minishell.h"

int main(int ac, char **av, char **envp)
{
	char	*readed;
	char	**input;
	printf("================ | Welcome to sara9osta |================\n");
	*get_env() = envp;
	while (1)
	{
		readed = readline("minishell$ ");
		if (!readed)
		{
			printf("exit\n");
			exit(0);
		}
		input = ft_split(readed, ' ');
		if (*readed)
			add_history(readed);
        cmnd_check(input, envp);
		// printf("--> %s\n", input);
		free(input);
	}
	return (0);
}