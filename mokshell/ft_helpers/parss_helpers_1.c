/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parss_helpers_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 17:07:37 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/10 15:18:48 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*make_heredoc_filename(void)
{
	int		i;
	char	*num;
	char	*tmp;
	char	*path;

	i = 0;
	while (1)
	{
		num = ft_itoa(i);
		if (!num)
			return (NULL);
		tmp = ft_strjoin("/tmp/.heredoc_tmp_", num);
		free(num);
		if (!tmp)
			return (NULL);
		if (access(tmp, F_OK) != 0)
		{
			path = tmp;
			break ;
		}
		free(tmp);
		i++;
	}
	return (path);
}

void	sigint_heredoc(int sig)
{
	(void)sig;
	signal(SIGINT, SIG_DFL);
	write(1, "\n", 1);
	set_exit_status(1);
	exit(1);
}

void	signals_heredoc(void)
{
	signal(SIGINT, sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

int	handle_heredocs_range(t_token *curr)
{
	pid_t	pid;
	int		status;
	char	*filename;

	if (curr->type == HEREDOC)
	{
		filename = make_heredoc_filename();
		if (!filename)
			return (1);
		g_flag_signal = 1;
		pid = fork();
		if (pid == 0)
		{
			g_flag_signal = 0;
			signals_heredoc();
			handle_heredoc_child(curr, filename);
		}
		waitpid(pid, &status, 0);
		if (check_status(status) == 7)
			return (7);
		free(curr->next->value);
		curr->next->value = filename;
		curr->type = REDIR_IN;
	}
	return (0);
}

void	set_exit_status(int status)
{
	get_shell()->exit_status = status;
}
