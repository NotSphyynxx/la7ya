
#include "includes/minishell.h"

void parss(t_parss *envr)
{
	char	*line;
	char	**buffer;
	t_token	*tokens;
	int		i;
	int		j;
	i = 0;
	j = 0;
	tokens = NULL;
	line = readline("Minishell:");
	if (!line)
		exit(1);
	if (*line)
		add_history(line);
	buffer = ft_split(line, ' ');
	while (buffer[i])
	{
		if (ft_strcmp(buffer[i], "<") == 0)
			add_token(&tokens, new_token(buffer[i], REDIR_IN));
		else if (ft_strcmp(buffer[i], ">") == 0)
			add_token(&tokens, new_token(buffer[i], REDIR_OUT));
		else if (buffer[i][0] == '>' && buffer[i][1] == '>' && buffer[i][2] == '>')
		{
			printf("Syntax error: unexpected '>>>'\n");
			return ;
		}
		else if (buffer[i][0] == '|' && buffer[i][1] == '|')
		{
            printf("Syntax error: unexpected '||' \n");
			printf("Invalid syntax.\n");
            return ;
		}
		else if (ft_strcmp(buffer[i], "|") == 0)
			add_token(&tokens, new_token(buffer[i], PIPE));
		else if (ft_strcmp(buffer[i], ">>") == 0)
			add_token(&tokens, new_token(buffer[i], REDIR_APPEND));
		else if (ft_strcmp(buffer[i], "<<") == 0)
			add_token(&tokens, new_token(buffer[i], HEREDOC));
		else if (buffer[i][0] == '$')
			add_token(&tokens, new_token(buffer[i], ENV_VAR));
		else
			add_token(&tokens, new_token(buffer[i], WORD));
		i++;
	}
	if (check_syntax(tokens) != 0)
	{
		printf("Invalid syntax.\n");
		return ;
	}
	t_token	*temp = tokens;
	while (temp)
	{
		printf("Token: type=%s, value=%s\n", type_to_string(temp->type), temp->value);
        temp = temp->next;
	}
	t_parss *tmp = envr;
	while (tokens)
	{
		char *tcm = tokens->content;
		if (tcm[0] == '$')
			break;
		tokens = tokens->next;
	}
	expand(tokens, tmp->env);
}