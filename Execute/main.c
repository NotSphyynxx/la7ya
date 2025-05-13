#include "minishell.h"

int main(int ac, char **av, char **envp)
{
    char *readed;
    t_exec exec;
    t_token *tokens;

    (void)ac;
    (void)av;

    printf("================ | Welcome to sara9osta | ================\n");
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
        if (tokens && is_simple_builtin_tokens(tokens))
        {
            char **input = tokens_to_cmd_without_redirs(tokens);
            if (input && input[0])
                builtin_check(input, *get_env());
            ft_free_str_array(input);
            free_tokens(tokens);
        }
        else if (tokens)
        {
            cmnd_check(NULL, *get_env(), &exec, tokens);
            free_tokens(tokens);
        }
        else
        {
            char **input = ft_split(readed, ' ');
            if (input && input[0])
                cmnd_check(input, *get_env(), &exec, NULL);
            ft_free_str_array(input);
        }
        free(readed);
    }
    return (0);
}
