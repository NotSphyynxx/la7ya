#include "minishell.h"

int main(int ac, char **av, char **envp)
{
    char *readed;
    t_exec exec;
    t_token *tokens;

    (void)ac;
    (void)av;

    printf("================ | Welcome to sara9osta |================\n");
    *get_env() = envp;

    // Signals
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
        tokens = tokenize_input(readed);
        if (tokens)
        {
            cmnd_check(NULL, envp, &exec, tokens);
            free_tokens(tokens);
        }
        else
        {
            // fallback for simple split-based commands (no pipes/redirs)
            char **input = ft_split(readed, ' ');
            if (input && input[0])
                cmnd_check(input, envp, &exec, NULL);
            ft_free_str_array(input);
        }
        free(readed);
    }

    return (0);
}
