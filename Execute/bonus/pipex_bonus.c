/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 23:12:48 by ildaboun          #+#    #+#             */
/*   Updated: 2025/03/08 00:10:18 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	handle_arg(void)
{
	write(2, "Error : less than 5 argument\n", 30);
	exit(1);
}

void	pipe_failed(void)
{
	write(2, "bash: pipe: Resource temporarily unavailable", 45);
	exit(1);
}

static void	wait_for_children(int cmd_nbr)
{
	int	i;

	i = 0;
	while (i < cmd_nbr)
	{
		wait(NULL);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_info		info;
	int			a;
	int			**fd;

	if (argc < 5)
		handle_arg();
	set_all(argc, argv, envp, &info);
	fd = allocate_fd(info.pipe_nbr);
	if (!fd)
		malloc_fd_fail(&info);
	a = -1;
	while (++a < info.pipe_nbr)
		create_pipes(a, fd);
	if (!info.envpp)
		env_fail(&info, fd);
	forking(argv, &info, fd);
	wait_for_children(info.cmd_nbr);
	pipe_free(&info, fd);
	free_fd(fd, info.pipe_nbr);
	close(info.outfile);
	close(info.infile);
}
