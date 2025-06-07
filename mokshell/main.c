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

void	read_and_exe(void)
{
	char	*readed;
	t_token	*tokens;
	char	**input;
	t_exec	exec;

	exec.gc_head = NULL;
	while (1)
	{
		readed = readline("minishell$ ");
		read_check(readed);
		if (*readed)
			add_history(readed);
		tokens = parss(readed);
		if (!tokens)
		{
			write(STDERR_FILENO, "minishell: failed to parse input\n", 34);
			continue ;
		}
		input = tokens_to_cmd(tokens, NULL);
		if (input || tokens)
			cmnd_check(input, *get_env(), tokens, &exec);
		gc_clear(&exec, readed, tokens, input);
	}
}
int	main(int ac, char **av, char **envp)
{

	if (ac > 2)
		return 0;
	if (!isatty(1) || !isatty(0))
		return (1);
	(void)av;
	printf("================ | Welcome to Sidna-shell | ================\n");
	init_shell(envp);
	read_and_exe();
	free_exp(*get_exp_list());
	ft_free_str_array(*get_env());
	return (0);
}
