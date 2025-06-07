#include "../minishell.h"

void	remove_export_node(t_exp **lst, char *key)
{
	t_exp	*cur;
	t_exp	*prev;

	prev = NULL;
	cur = *lst;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				*lst = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}
