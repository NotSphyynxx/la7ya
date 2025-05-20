#include "../minishell.h"

int	is_builtin(char **input)
{
	if (!input || !(*input))
        return (0);
    else if (ft_strcmp(input[0], "echo") == 0)
		return (1);
    else if (ft_strcmp(input[0], "env") == 0)
        return (1);
    else if (ft_strcmp(input[0], "pwd") == 0)
        return (1);
    else if (ft_strcmp(input[0], "cd") == 0)
        return (1);
    else if (ft_strcmp(input[0], "export") == 0)
        return (1);
    else if (ft_strcmp(input[0], "unset") == 0)
        return (1);
    else if (ft_strcmp(input[0], "exit") == 0)
        return (1);
    return (0);
}