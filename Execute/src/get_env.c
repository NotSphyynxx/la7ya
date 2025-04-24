/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:20:57 by ildaboun          #+#    #+#             */
/*   Updated: 2025/03/07 22:50:55 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_env(char **env)
{
	char	**path;
	int		i;

	if (!env)
	{
		write(2, "bash: command: command not found", 33);
		exit(1);
	}
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			env[i] = ft_strnstr(env[i], "/", ft_strlen(env[i]));
			path = ft_split(env[i], ':');
			if (!path)
			{
				write(2, "bash: command: command not found", 33);
				exit(1);
			}
			return (path);
		}
		i++;
	}
	return (NULL);
}

void	env_fail(char **envp, int file, int fd[2])
{
	if (!envp)
	{
		close(file);
		close(fd[0]);
		close(fd[1]);
		write(2, "bash: command: command not found", 33);
		exit(1);
	}
}

void	fail(int file, int fd[2])
{
	close(file);
	close(fd[0]);
	close(fd[1]);
	write(2, "bash: dup2: Bad file descriptor", 32);
	exit(1);
}
