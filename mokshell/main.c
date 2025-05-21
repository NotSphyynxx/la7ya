/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:41:04 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/05/21 17:23:44 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*readed;
	t_token	*tokens;
	char	**input;
	t_exec	exec;

	(void)ac;
	(void)av;
	printf("================ | Welcome to Sidna-shell | ================\n");
	init_shell(envp);
	while (1)
	{
		readed = readline("minishell$ ");
		read_check(readed);
		if (*readed)
			add_history(readed);
		tokens = parss(readed);
		input = tokens_to_cmd(tokens, NULL);
		if (tokens || input)
			cmnd_check(input, *get_env(), tokens, &exec);
		leaks_handle(readed, tokens, input, &exec);
	}
	return (0);
}
