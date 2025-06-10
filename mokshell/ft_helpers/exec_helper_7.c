/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper_7.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:58:26 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/08 15:49:31 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wait_for_children(void)
{
	int			status;
	pid_t		pid;
	int			sig;
	static int	printed;

	printed = 0;
	pid = wait(&status);
	while (pid > 0)
	{
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGQUIT && printed == 0 && is_there(*get_line()))
			{
				ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
				printed = 1;
			}
		}
		update_exit_status(status);
		pid = wait(&status);
	}
}


void	update_exit_status(int status)
{
	if (WIFEXITED(status))
		get_shell()->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		get_shell()->exit_status = 128 + WTERMSIG(status);
}

int	has_equal_sign(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	is_append_export(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i] == '+' && av[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

t_shell	*get_shell(void)
{
	static t_shell	shell;

	return (&shell);
}
