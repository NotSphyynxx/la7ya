#include "../minishell.h"

void	add_exp_back(t_exp **lst, t_exp *new)
{
	t_exp *tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_exp	*find_exp(t_exp *list, char *key)
{
	while (list)
	{
		if (ft_strcmp(list->key, key) == 0)
			return (list);
		list = list->next;
	}
	return (NULL);
}

int	check_valid_key(char *key)
{
	if (!ft_isalpha(*key) && *key != '_')
		return (0);
	while(*key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (0);
		key++;
	}
	return (1);
}
void ft_free_str_array(char **arr)
{
    int i = 0;
    while (arr && arr[i])
    {
        free(arr[i++]);
    }
    free(arr);
}


char *find_command_path(char *cmd, t_exec *exec)
{
	char	*path_env;
	char	**paths;
	char	*tmp;
	int		i;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = get_env_value("PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
		{
			ft_free_str_array(paths);
			return (NULL);
		}
		exec->cmnd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!exec->cmnd_path)
		{
			ft_free_str_array(paths);
			return (NULL);
		}
		if (access(exec->cmnd_path, X_OK) == 0)
		{
			ft_free_str_array(paths);
			return (exec->cmnd_path);
		}
		free(exec->cmnd_path);
		i++;
	}
	ft_free_str_array(paths);
	return (NULL);
}