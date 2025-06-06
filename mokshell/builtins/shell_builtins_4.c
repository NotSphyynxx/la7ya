#include "../minishell.h"

void	join_path(char **pwd, char *addition)
{
	char *tmp;
	char *new_pwd;

	// Avoid adding slash if pwd already ends with '/'
	if ((*pwd)[ft_strlen(*pwd) - 1] == '/')
		tmp = ft_strdup(*pwd);
	else
		tmp = ft_strjoin(*pwd, "/");

	new_pwd = ft_strjoin(tmp, addition);
	free(tmp);
	free(*pwd);
	*pwd = new_pwd;
}


void	update_pwd_on_cd(char *path)
{
	char *current_pwd;

	// If absolute path, reset it directly
	if (path[0] == '/')
	{
		free(*get_pwd_storage());
		*get_pwd_storage() = ft_strdup(path);
	}
	// if "..", and we can’t getcwd(), join ".."
	else if (!ft_strcmp(path, ".."))
	{
		current_pwd = getcwd(NULL, 0);
		if (!current_pwd)
			join_path(get_pwd_storage(), "..");
		else
		{
			// reset to real PWD when back to good state
			free(*get_pwd_storage());
			*get_pwd_storage() = current_pwd;
			return ;
		}
	}
	// Otherwise, join relative path
	else
		join_path(get_pwd_storage(), path);

	update_env_value("PWD", *get_pwd_storage());
}


void	update_env_value(char *key, char *value)
{
	char	*var;
	char	*tmp;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return ;
	var = ft_strjoin(tmp, value);
	free(tmp);
	if (!var)
		return ;
	realloc_env(var);
	free(var);
}
