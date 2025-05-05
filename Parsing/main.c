/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:53:56 by bael-bad          #+#    #+#             */
/*   Updated: 2025/05/05 17:16:28 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    (void)env;
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
    while (1)
    {
        parss();
    }
}
