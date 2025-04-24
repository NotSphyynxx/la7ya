/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_access.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:23:25 by ildaboun          #+#    #+#             */
/*   Updated: 2025/03/09 19:21:09 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_them(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static char	*handle_savee(char *save)
{
	if (!save)
		return (NULL);
	return (save);
}

static char	*handle_jpathh(char *jpath)
{
	if (!jpath)
		return (NULL);
	return (jpath);
}

char	*the_path(char *path, char *cmd)
{
	char	*jpath;
	char	*save;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) != 0)
			write(2, "Command not found or not executable\n", 37);
		return (ft_strdup(cmd));
	}
	save = ft_strjoin(path, "/");
	handle_savee(save);
	jpath = NULL;
	jpath = ft_strjoin(save, cmd);
	handle_jpathh(jpath);
	free(save);
	return (jpath);
}

char	*append_access(char **path, char *cmd)
{
	int		i;
	char	*jpath;
	char	**split_cmd;

	i = 0;
	split_cmd = ft_split(cmd, ' ');
	if (!split_cmd)
		handle_path(split_cmd);
	while (path[i])
	{
		jpath = the_path(path[i], split_cmd[0]);
		handle_jpathh(jpath);
		if (access(jpath, F_OK | X_OK) == 0)
			return (free_them(split_cmd), jpath);
		free(jpath);
		i++;
	}
	free_them(split_cmd);
	return (NULL);
}
