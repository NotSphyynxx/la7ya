#include "../minishell.h"

void	*gc_malloc(size_t size, t_exec *exec)
{
	void		*ptr;
	t_gc_node	*new_node;

	
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	new_node = malloc(sizeof(t_gc_node));
	if (!new_node)
		return (free(ptr), NULL);
	new_node->ptr = ptr;
	new_node->next = exec->gc_head;
	exec->gc_head = new_node;
	return (ptr);
}

void	gc_clear(t_exec *exec, char *readed, t_token *tokens, char **input)
{
	t_gc_node *tmp;

	while (exec->gc_head)
	{
		tmp = exec->gc_head->next;
		if (exec->gc_head->ptr)
			free(exec->gc_head->ptr);
		free(exec->gc_head);
		exec->gc_head = tmp;
	}
	if (readed)
		free(readed);
	if (tokens)
		free_tokens(tokens);
	ft_free_str_array(input);
}

