/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 15:01:39 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/09 16:31:22 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_flag_signal;

void	read_and_exe(void)
{
	char	*readed;
	t_token	*tokens;
	char	**input;
	t_exec	exec;

	exec.gc_head = NULL;
	while (1)
	{
		g_flag_signal = 0;
		readed = readline("minishell$ ");
		read_check(readed);
		if (*readed)
			add_history(readed);
		*get_line() = readed;
		tokens = parss(readed);
		if (!tokens)
			continue ;
		input = tokens_to_cmd(tokens, NULL);
		if (input || tokens)
			cmnd_check(input, *get_env(), tokens);
		gc_clear(&exec, &readed, tokens, input);
	}
}

int	main(int ac, char **av, char **envp)
{
	if (ac > 2)
		return (0);
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
