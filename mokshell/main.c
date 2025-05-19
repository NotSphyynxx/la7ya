#include "minishell.h"

int main(int ac, char **av, char **envp)
{
    char *readed;
    t_exec exec;
    t_token *tokens;

    (void)ac;
    (void)av;
    t_parss path;

    printf("================ | Welcome to sara9osta | ================\n");
    *get_env() = init_env(envp);
	init_export_list();
    
    // Signals
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
    
    while (1)
    {
        path.env = *get_env();
        readed = readline("minishell$ ");
        if (!readed)
        {
            printf("exit\n");
            exit(0);
        }
        if (*readed)
            add_history(readed);
        tokens = parss(readed, &path);
        char **input = tokens_to_cmd(tokens, NULL);
        if (tokens || input)
        {
            cmnd_check(input, *get_env(), &exec, tokens);
            free_tokens(tokens);
            ft_free_str_array(input);
        }
        free(readed);
    }
    return (0);
}
