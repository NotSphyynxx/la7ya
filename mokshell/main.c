/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:06:56 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/07/09 13:09:45 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_flag_signal;

void	read_and_exe(void)
{
	char	*readed;
	t_token	*tokens;
	char	**input;

	while (1)
	{
		g_flag_signal = 0;
		readed = readline("minishell$ ");
		read_check(readed);
		if (*readed)
			add_history(readed);
		*get_line() = readed;
		tokens = parss(readed);
		// while (tokens)
		// {
		// 	printf("tokens: %s\n", tokens->value);
		// 	tokens = tokens->next;
		// }
		if (!tokens)
		{
			free_all_fd();
			free_line(&readed);
			continue ;
		}
		input = tokens_to_cmd(tokens, NULL);
		if (input || tokens)
			cmnd_check(input, *get_env(), tokens);
		gc_clear(&readed, tokens, input);
	}
}

int	main(int ac, char **av, char **envp)
{
	if (ac > 1)
		return (0);
	if (!isatty(1) || !isatty(0))
		return (1);
	(void)av;
	init_shell(envp);
	read_and_exe();
	free_exp(*get_exp_list());
	ft_free_str_array(*get_env());
	return (0);
}
