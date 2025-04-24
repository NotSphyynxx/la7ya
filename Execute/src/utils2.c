/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:20:01 by ildaboun          #+#    #+#             */
/*   Updated: 2025/03/09 19:21:38 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(char *file_name, int file_flag, int fd[2])
{
	int	file;

	file = -1;
	if (file_flag == 0)
		file = open(file_name, O_RDONLY);
	else if (file_flag == 1)
		file = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file == -1)
	{
		close(fd[0]);
		close(fd[1]);
		write(2, "bash: file_name: No such file or directory\n", 43);
		exit(1);
	}
	return (file);
}

static char	*get_them(char **argv, char **envp, int flag, int fd[2])
{
	char	**path;
	char	*jpath;

	path = get_env(envp);
	handle_path(path);
	if (!flag)
		jpath = append_access(path, argv[2]);
	else
		jpath = append_access(path, argv[3]);
	if (!jpath)
	{
		close(fd[0]);
		close(fd[1]);
		handle_jpath(jpath);
	}
	return (jpath);
}

void	dad(int fd[2], char **argv, char **envp)
{
	int		out_f;
	char	**s_args;
	char	*jpath;

	close(fd[1]);
	out_f = open_file(argv[4], 1, fd);
	env_fail(envp, out_f, fd);
	if (dup2(out_f, STDOUT_FILENO) == -1)
		fail(out_f, fd);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		fail(out_f, fd);
	close(fd[0]);
	close(out_f);
	s_args = ft_split(argv[3], ' ');
	if (!s_args)
		env_fail(s_args, out_f, fd);
	jpath = get_them(argv, envp, 1, fd);
	if (execve(jpath, s_args, envp) == -1)
	{
		free_them(s_args);
		free(jpath);
		write(2, "bash: command: command not found\n", 33);
		exit(1);
	}
}

void	kiddo(int fd[2], char **argv, char **envp)
{
	int		inpu_f;
	char	**s_args;
	char	*jpath;

	close(fd[0]);
	inpu_f = open_file(argv[1], 0, fd);
	env_fail(envp, inpu_f, fd);
	if (dup2(inpu_f, STDIN_FILENO) == -1)
		fail(inpu_f, fd);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		fail(inpu_f, fd);
	close(fd[1]);
	close(inpu_f);
	s_args = ft_split(argv[2], ' ');
	if (!s_args)
		env_fail(s_args, inpu_f, fd);
	jpath = get_them(argv, envp, 0, fd);
	if (execve(jpath, s_args, envp) == -1)
	{
		free_them(s_args);
		free(jpath);
		write(2, "bash: command: command not found\n", 33);
		exit(1);
	}
}

void	handle_dup(void)
{
	write(2, "bash: dup2: Bad file descriptor\n", 33);
	exit(1);
}
