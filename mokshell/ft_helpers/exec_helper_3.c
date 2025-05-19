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