/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:12:23 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/04/21 18:22:26 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

int main(int ac, char **av, char **envp)
{
	printf("================ | Welcome to sara9osta |================\n");
	char *input;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			exit(0);
		}
		if (*input)
			add_history(input);
        execute (input, envp);
		free(input);
	}
	return (0);
}