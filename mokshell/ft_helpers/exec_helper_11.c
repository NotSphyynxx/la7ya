#include "../minishell.h"

t_token	**get_token_list(void)
{
	static t_token	*tokens = NULL;

	return (&tokens);
}
void	free_tokens_list(void)
{
	t_token	*current;
	t_token	*next;

	current = *get_token_list();
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	*get_token_list() = NULL;
}
