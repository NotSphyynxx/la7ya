#include "../minishell.h"

char	**get_line(void)
{
	static char	*line;
	return (&line);
}
