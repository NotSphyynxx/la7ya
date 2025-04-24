/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 23:12:48 by ildaboun          #+#    #+#             */
/*   Updated: 2025/03/09 18:10:08 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_arg(int argc)
{
	if (argc != 5)
	{
		write(2, "Error : it must takes 5 Argumemts\n", 34);
		exit(1);
	}
}

void	handle_path(char **path)
{
	if (!path)
	{
		write(2, "bash: command: command not found\n", 33);
		exit(1);
	}
}

void	handle_jpath(char *jpath)
{
	if (!jpath)
	{
		write(2, "bash: command: command not found\n", 33);
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	proc_id;
	pid_t	id;

	handle_arg(argc);
	if (pipe(fd) == -1)
		pipe_fail();
	proc_id = fork();
	if (proc_id == -1)
		fork_fail(fd);
	if (!proc_id)
		kiddo(fd, argv, envp);
	id = fork();
	if (id == -1)
		fork_fail(fd);
	if (!id)
		dad(fd, argv, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(proc_id, NULL, 0);
	waitpid(id, NULL, 0);
}
