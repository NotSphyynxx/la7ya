#include "minishell.h"

int main(int ac, char **av, char **envp)
{
	char	*readed;
	char	**input;
	printf("================ | Welcome to sara9osta |================\n");
	*get_env() = envp;
	t_exec exec;
	t_token *temp;

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
		if (*readed)
			add_history(readed);
    	if (has_redirection(readed))
    	{
				t_token *tokens = tokenize_input(readed);
				cmnd_check(NULL, envp, &exec, tokens);
				free_tokens(tokens);
   		}
		else
    	{
        	char **input = ft_split(readed, ' ');
        	if (input && input[0])
       		{
            	cmnd_check(input, envp, &exec, NULL);
            	ft_free_str_array(input); // <--- free here
       		}
    	}
    	free(readed);
	}
	free(input);
	return (0);
}