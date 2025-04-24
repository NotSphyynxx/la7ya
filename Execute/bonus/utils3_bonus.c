/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:42:22 by ildaboun          #+#    #+#             */
/*   Updated: 2025/03/08 00:21:32 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	fill_here_doc(char	**argv, int fd[2])
{
	char	*line;

	line = get_next_line(0);
	while (line)
	{
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
		{
			free(line);
			close(fd[0]);
			close(fd[1]);
			return ;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	free(line);
	close(fd[0]);
	close(fd[1]);
}

void	the_doc_thing(char **argv)
{
	pid_t	id;
	int		fd[2];

	if (pipe(fd) == -1)
		pipe_failed();
	id = fork();
	fork_error(id);
	if (!id)
	{
		close(fd[0]);
		fill_here_doc(argv, fd);
		close(fd[1]);
		exit(0);
	}
	else
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
			handle_dup();
		close(fd[0]);
		close(fd[1]);
		wait(NULL);
	}
}

void	create_process(char **argv, int	**fd, int a, t_info *info)
{
	pid_t	proc_id;

	proc_id = fork();
	if (proc_id == -1)
		env_fail(info, fd);
	if (!proc_id)
	{
		if (a == info->cmd_nbr - 1)
		{
			dad(fd, argv, info, a);
			return ;
		}
		if (a == info->cmd_nbr - 1)
			exit(0);
		kiddo(fd, argv, info, a);
		exit(0);
	}
	else
	{
		if (a == info->cmd_nbr - 1)
			return ;
		close(fd[a][1]);
		if (dup2(fd[a][0], STDIN_FILENO) == -1)
			handle_dup();
	}
}

void	handle_dup(void)
{
	write(2, "bash: dup2: Bad file descriptor", 32);
	exit(1);
}

void	fork_error(pid_t i)
{
	if (i == -1)
	{
		write(2, "bash: fork: Resource temporarily unavailable", 45);
		exit(1);
	}
}
