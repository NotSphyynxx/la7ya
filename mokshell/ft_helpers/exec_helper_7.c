/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper_7.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:22:54 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/05/22 15:25:33 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wait_for_children(void)
{
	int	status;
	pid_t	pid;

	while ((pid = wait(&status)) > 0)
	{
		update_exit_status(status);
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

t_shell *get_shell(void)
{
    static t_shell	shell;
    return (&shell);
}
