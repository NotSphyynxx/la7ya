#include "../minishell.h"

void	check_path(char *path)
{
	int i;

	i = 0;
	free(*get_pwd_storage());
	while (path[i] && path[i] == '/')
		i++;
	if (i == (int)ft_strlen(path))
		*get_pwd_storage() = ft_strdup("/");
	else
		*get_pwd_storage() = ft_strdup(path);
}

void	check_double_dots(char *path)
{
	int			len;
	char	*new_pwd;


	len = ft_strlen(*get_pwd_storage());
	if (len > 1 && (*get_pwd_storage())[len - 1] == '/')
		len--;
	while (len > 0 && (*get_pwd_storage())[len - 1] != '/')
		len--;
	if (len == 0)
		len = 1;
	new_pwd = ft_substr(*get_pwd_storage(), 0, len);
	update_pwd_stock(new_pwd);
}

void	check_dot(char *path)
{
	char		*tmp;
	char	*new_pwd;

	if ((*get_pwd_storage())[ft_strlen(*get_pwd_storage()) - 1] == '/')
		tmp = ft_strdup(*get_pwd_storage());
	else
		tmp = ft_strjoin(*get_pwd_storage(), "/");
	new_pwd = ft_strjoin(tmp, path);
	free(tmp);
	update_pwd_stock(new_pwd);
}

void	update_pwd_on_cd(char *path)
{
	char	*cwd;

	if (path[0] == '/')
		check_path(path);
	else
	{
		cwd = getcwd(NULL, 0);
		if (cwd)
			update_pwd_stock(cwd);
		else
		{
			if (ft_strcmp(path, "..") == 0)
				check_double_dots(path);
			else if (ft_strcmp(path, ".") != 0)
				check_dot(path);
		}
	}
	update_env_value("PWD", *get_pwd_storage());
}

void	update_pwd_stock(char *new_pwd)
{
	free(*get_pwd_storage());
	*get_pwd_storage() = new_pwd;
}
