#include "minishell.h"

int main(int ac, char **av, char **envp)
{
	char	*readed;
	char	**input;
	printf("================ | Welcome to sara9osta |================\n");
	*get_env() = envp;
	t_exec exec;

    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
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
		parss(input);
        cmnd_check(input, envp, &exec);
		free(input);
	}
	return (0);
}