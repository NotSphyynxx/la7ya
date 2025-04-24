/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:20:57 by ildaboun          #+#    #+#             */
/*   Updated: 2025/03/07 22:39:38 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	env_fail(t_info *info, int **fd)
{
	close(info->outfile);
	close(info->infile);
	pipe_free(info, fd);
	write(2, "bash: command: command not found", 33);
	exit(1);
}

void	set_all(int argc, char **argv, char **envp, t_info *info)
{
	if (!ft_strcmp(argv[1], "here_doc"))
		set_info(argv, argc, info, envp);
	else
		set_info2(argv, argc, info, envp);
}

void	handle_path(char **path)
{
	if (!path)
	{
		write(2, "bash: command: command not found", 33);
		exit(1);
	}
}

void	handle_jpath(char *jpath)
{
	if (!jpath)
	{
		write(2, "bash: command: command not found", 33);
		exit(1);
	}
}
