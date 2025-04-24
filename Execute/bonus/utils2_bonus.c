/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:20:01 by ildaboun          #+#    #+#             */
/*   Updated: 2025/03/09 19:27:04 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	open_file(char *file_name, int file_flag, t_info *info)
{
	int	fd;

	fd = -1;
	if (file_flag == 0)
		fd = open(file_name, O_RDONLY);
	else if (file_flag == 1)
		fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file_flag == 2)
		fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		close(info->outfile);
		close(info->infile);
		write(2, "bash: file_name: No such file or directory", 43);
		exit(1);
	}
	return (fd);
}

static char	*get_them(char **argv, t_info *info, int flag, int **fd)
{
	char	**path;
	char	*jpath;

	path = get_env(info->envpp);
	handle_path(path);
	if (!flag)
		jpath = append_access(path, argv[(info->csplit) + info->a]);
	else
		jpath = append_access(path, argv[(info->psplit) + info->a]);
	if (!jpath)
		env_fail(info, fd);
	return (jpath);
}

void	dad(int **fd, char **argv, t_info *info, int a)
{
	char	**s_args;
	char	*jpath;

	last_step(argv, info, fd);
	if (a >= info->pipe_nbr)
		a = info->pipe_nbr - 1;
	info->a = a;
	close(fd[a][1]);
	if (dup2(fd[a][0], STDIN_FILENO) == -1)
		handle_dup();
	close(fd[a][0]);
	if (!info->envpp)
		env_fail(info, fd);
	s_args = ft_split(argv[(info->psplit) + a], ' ');
	if (!s_args)
		env_fail(info, fd);
	jpath = get_them(argv, info, 1, fd);
	if (execve(jpath, s_args, info->envpp) == -1)
	{
		free_them(s_args);
		free(jpath);
		write(2, "bash: command: command not found", 33);
		exit(1);
	}
}

void	kiddo(int **fd, char **argv, t_info *info, int a)
{
	char	**s_args;
	char	*jpath;

	close(fd[a][0]);
	if (dup2(fd[a][1], STDOUT_FILENO) == -1)
		handle_dup();
	close(fd[a][1]);
	if (!info->envpp)
		env_fail(info, fd);
	info->a = a;
	s_args = ft_split(argv[(info->csplit) + a], ' ');
	if (!s_args)
		env_fail(info, fd);
	jpath = get_them(argv, info, 0, fd);
	if (execve(jpath, s_args, info->envpp) == -1)
	{
		free_them(s_args);
		free(jpath);
		write(2, "bash: command: command not found", 33);
		exit(1);
	}
}
