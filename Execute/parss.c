
#include "minishell.h"

t_token	*parss(char *line ,t_parss *envr)
{
	t_token	*tokens;
	char	**buffer;
	int		i;

	// int		j;
	i = 0;
	// j = 0;
	tokens = NULL;
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
			return NULL;
		}
		else if (buffer[i][0] == '|' && buffer[i][1] == '|')
		{
            printf("Syntax error: unexpected '||' \n");
			printf("Invalid syntax.\n");
            return NULL;
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
		return NULL;
	}
	t_token	*temp = tokens;
	while (temp)
	{
		printf("Token: type=%s, value=%s\n", type_to_string(temp->type), temp->value);
        temp = temp->next;
	}
	t_parss *tmp = envr;
	temp = tokens;
	while (temp)
	{
		char *tcm = temp->value;
		if (tcm[0] == '$')
			expand(temp, tmp->env);
		temp = temp->next;
	}
	if (!tokens)
		printf("ana hmar\n");
	return (tokens);
}