
#include "includes/minishell.h"

void sigint_handler(int sig)
{
    (void)sig;
    rl_replace_line("", 0);
    write(1, "\n", 1);
    rl_on_new_line();
    rl_redisplay();
}


int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    t_parss path;
    
    path.env = env;
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
    while (1)
    {
        parss(&path);
        continue;
    }
}
