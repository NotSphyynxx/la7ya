#include "../minishell.h"

/* parse key, value and detect “+=” */
/* parse key, val, detect += — no validation or frees here */
static void	parse_export_arg(char *arg, char **key, char **val, int *append)
{
	char	*plus;
	char	*eq;

	*append = 0;
	plus = ft_strnstr(arg, "+=", ft_strlen(arg));
	if (plus)
	{
		*append = 1;
		*key    = ft_substr(arg, 0, plus - arg);
		*val    = ft_strdup(plus + 2);
	}
	else if ((eq = ft_strchr(arg, '=')))
	{
		*key = ft_substr(arg, 0, eq - arg);
		*val = ft_strdup(eq + 1);
	}
	else
	{
		*key = ft_strdup(arg);
		*val = NULL;
	}
}


/* update or create in export list */
/* update or create in export list */
static void	apply_export_list(char *key, char *val, int append)
{
	t_exp	*ex;
	char	*tmp;

	ex = find_exp(*get_exp_list(), key);
	if (ex)
	{
		if (val)
		{
			if (append)
			{
				tmp = ex->value;
				ex->value = ft_strjoin(tmp, val);
				free(tmp);
			}
			else
			{
				free(ex->value);
				ex->value = ft_strdup(val);
			}
		}
	}
	else
	{
		/* ALWAYS add a new export entry, even if val == NULL */
		if (append && !val)
			val = ft_strdup("");
		add_exp_back(get_exp_list(),
			new_exp_node(ft_strdup(key),
				(val ? ft_strdup(val) : NULL)));
	}
}


/* sync one variable into the env array */
static void	sync_env_var(char *key, char *val)
{
	char	*entry;

	if (!val)
		return ;
	entry = ft_strjoin(key, "=");
	entry = ft_strjoin(entry, val);
	adjust_env(entry, key);
	free(entry);
}

/* the main export builtin */
/* the export builtin, doing validation, list‐update, env‐sync, frees */
int	shell_export(char **av)
{
	int		i;
	int		append;
	int		err;
	char	*key;
	char	*val;
	t_exp	*ex;   /* <--- new */

	i   = 1;
	err = 0;
	if (!av[1])
	{
		printf_export_list();
		update_exit_status(0);
		return (0);
	}
	while (av[i])
	{
		parse_export_arg(av[i], &key, &val, &append);

		if (!check_valid_key(key))
		{
			error_export(&key, &val);
			err = 1;
		}
		else
		{
			apply_export_list(key, val, append);

			/* if we have a value, sync the right one: */
			if (val)
			{
				if (append)
				{
					ex = find_exp(*get_exp_list(), key);
					sync_env_var(key, ex->value);
				}
				else
					sync_env_var(key, val);
			}

			free(key);
			free(val);
		}
		i++;
	}
	update_exit_status(err);
	return (err);
}
