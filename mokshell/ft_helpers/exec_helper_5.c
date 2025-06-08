/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:58:07 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/08 15:10:40 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char **input)
{
	if (!input || !(*input))
		return (0);
	else if (ft_strcmp(input[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(input[0], "env") == 0)
		return (1);
	else if (ft_strcmp(input[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(input[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(input[0], "export") == 0)
		return (1);
	else if (ft_strcmp(input[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(input[0], "exit") == 0)
		return (1);
	return (0);
}

void	init_shell(char **envp)
{
	*get_env() = init_env(envp);
	init_export_list();
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	init_pwd();
}

void	read_check(char *readed)
{
	if (!readed)
	{
		printf("exit\n");
		free_exp(*get_exp_list());
		ft_free_str_array(*get_env());
		exit(0);
	}
}

int	there_is_red(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp)
	{
		if (temp->type == REDIR_OUT || temp->type == REDIR_APPEND
			|| temp->type == REDIR_IN || temp->type == HEREDOC)
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	built_with_red_check(char **input, char **envp, t_token *tokens)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		if (apply_redirections(tokens, NULL) == -1)
			exit(1);
		builtin_check(input, envp);
		exit(0);
	}
	waitpid(pid, &status, 0);
	update_exit_status(status);
}
