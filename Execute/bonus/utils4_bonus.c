/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:40:36 by ildaboun          #+#    #+#             */
/*   Updated: 2025/03/07 02:51:10 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	pipe_free(t_info *info, int **fd)
{
	int	a;

	a = 0;
	while (a < info->pipe_nbr)
	{
		close(fd[a][0]);
		close(fd[a][1]);
		a++;
	}
}

void	set_info2(char **argv, int argc, t_info *info, char **envp)
{
	if (argc < 5)
	{
		write(2, "Error : program has less than 5 Argumemts ", 43);
		exit(1);
	}
	info->envpp = envp;
	info->lst_argm = argc;
	info->psplit = 3;
	info->csplit = 2;
	info->cmd_nbr = argc - 3;
	info->pipe_nbr = info->cmd_nbr - 1;
	info->outfile = open_file(argv[argc - 1], 1, info);
	info->infile = open_file(argv[1], 0, info);
	if (dup2(info->infile, STDIN_FILENO) == -1)
	{
		close(info->outfile);
		close(info->infile);
		handle_dup();
	}
	close(info->infile);
}

void	set_info(char **argv, int argc, t_info *info, char **envp)
{
	if (argc < 6)
	{
		write(2, "Error : program has less than 6 Argumemts ", 43);
		exit(1);
	}
	info->envpp = envp;
	info->lst_argm = argc;
	info->cmd_nbr = argc - 4;
	info->psplit = 4;
	info->csplit = 3;
	info->pipe_nbr = info->cmd_nbr - 1;
	info->outfile = -1;
	write(1, "here_doc> ", 10);
	the_doc_thing(argv);
}

void	create_pipes(int a, int **fd)
{
	if (pipe(fd[a]) == -1)
	{
		free_fd(fd, a);
		pipe_failed();
	}
}

void	forking(char **argv, t_info *info, int **fd)
{
	int	a;

	a = 0;
	while (a < info->cmd_nbr)
	{
		create_process(argv, fd, a, info);
		a++;
	}
}
