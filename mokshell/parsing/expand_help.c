#include "../minishell.h"

static void	append_exit_status(char **result, int *i)
{
	char	*tmp;
	char	*exit_status_str;

	exit_status_str = ft_itoa(get_shell()->exit_status);
	tmp = *result;
	*result = ft_strjoin(tmp, exit_status_str);
	free(tmp);
	free(exit_status_str);
	(*i)++;
}

static void	append_env_variable(char **result, char *line, int *i, int *flag)
{
	int		var_start;
	char	*var_name;
	char	*val;
	char	*tmp;

	var_start = *i;
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		(*i)++;
	var_name = ft_substr(line, var_start, *i - var_start);
	val = ft_strdup(get_env2_value(var_name));
	tmp = *result;
	*result = ft_strjoin(tmp, val);
	free(tmp);
	free(val);
	free(var_name);
	*flag = 1;
}

static void	handle_dollar(char *line, int *i, int *start, char **result, int *flag)
{
	char	*before;
	char	*tmp;

	before = ft_substr(line, *start, *i - *start);
	tmp = *result;
	*result = ft_strjoin(tmp, before);
	free(tmp);
	free(before);
	(*i)++;
	if (line[*i] == '?')
		append_exit_status(result, i);
	else if (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		append_env_variable(result, line, i, flag);
	else
	{
		tmp = *result;
		*result = ft_strjoin(tmp, "$");
		free(tmp);
	}
	*start = *i;
}

char	*expand_variable(char *line, int *flag)
{
	int		i;
	int		start;
	char	*result;
	char	*remaining;
	char	*tmp;

	i = 0;
	start = 0;
	result = ft_strdup("");
	while (line[i])
	{
		if (line[i] == '$')
			handle_dollar(line, &i, &start, &result, flag);
		else
			i++;
	}
	if (start < i)
	{
		remaining = ft_substr(line, start, i - start);
		tmp = result;
		result = ft_strjoin(tmp, remaining);
		free(tmp);
		free(remaining);
	}
	return (result);
}
