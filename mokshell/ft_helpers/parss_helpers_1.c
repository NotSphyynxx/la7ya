#include "../minishell.h"

static char *make_heredoc_filename(void)
{
    int     i = 0;
    char    *num;
    char    *tmp;
    char    *path;

    while (1)
    {
        num = ft_itoa(i);
        if (!num)
            return NULL;
        tmp = ft_strjoin("/tmp/.heredoc_tmp_", num);
        free(num);
        if (!tmp)
            return NULL;
        if (access(tmp, F_OK) != 0)
        {
            path = tmp;
            break;
        }
        free(tmp);
        i++;
    }
    return path;
}
// static void	handle_heredoc_child(t_token *curr, char *filename)
// {
// 	int		fd;
//     int     i;
// 	char	*line;
//     char *temp_line;
//     t_token    *del = curr;
//     char    *string;
//     t_token *token;

//     i = 0;
//     token = curr;
//         if (curr->type == HEREDOC)
//             del = curr->next;
//         printf("%s\n", del->value);
//     // printf("%s\n", del);
//     curr = token;
//     string = del->value;
//     string = strip_quotes(string);
// 	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd < 0)
// 	{
// 		perror("heredoc tmp file error");
// 		exit(1);
// 	}
//     printf("ddd%s\n", string);
// 	while (1)
// 	{
// 		line = readline("> ");
//         printf("%s\n", string);
//         printf("line %s\n", line);
//         if (ft_strcmp(line, string) == 0)
//         {
//             printf("here\n");
//             free(line);
//             break;
//         }
        
// 		// if (!line || ft_strcmp(line, curr->next->value) == 0)
// 		// {
// 		// 	free(line);
// 		// 	break;
//         // }
//         // temp_line = line;
//         curr = curr->next;
//         if (ft_strchr(line, '$') && curr->was_double == 0 && curr->was_single == 0)
//         {
//             line = expand_var(line);
//             // free(temp_line);
//         }
// 		write(fd, line, ft_strlen(line));
// 		write(fd, "\n", 1);
// 		free(line);
//     }
// 	close(fd);
// 	exit(0);
// }
static void	handle_heredoc_child(t_token *curr, char *filename)
{
	int		fd;
	char	*line;
    char *temp_line;
    char *tmp;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("heredoc tmp file error");
		exit(1);
	}
    curr = curr->next;
    if (curr->was_double == 1 || curr->was_single == 1)
    {
        tmp = ft_strip_quotes(curr->value);
    }
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, curr->value) || !ft_strcmp(line, tmp))
		{
			free(line);
			break;
		}
        if (curr->was_double == 0 && curr->was_single == 0)
        {
            temp_line = line;
            line = expand_var(line);
            free(temp_line);
        }
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
        if (tmp)
            free(tmp);
	}
	close(fd);
	exit(0);
}

void handle_heredocs_range(t_token *curr)
{
    pid_t    pid;
    int      status;
    char    *filename;

    if (curr->type == HEREDOC)
    {
        filename = make_heredoc_filename();
        if (!filename)
            return;
        pid = fork();
        if (pid == 0)
            handle_heredoc_child(curr, filename);
        waitpid(pid, &status, 0);
        update_exit_status(status);
        free(curr->next->value);
        curr->next->value = filename;
        curr->type = REDIR_IN;
    }
}

int check_all(t_token **tokens, char *line, int *i)
{
    while (line[*i])
    {
        if (ft_isspace(line[*i]))
        {
            (*i)++;
            continue;
        }
        if (line[*i] == '|')
        {
            if (!check_pipe(tokens, line, i))
                return (0);
        }
        else if (line[*i] == '>' || line[*i] == '<')
        {

            if (!check_heredoc(tokens, line, i))
                return (0);
        }
        else
            if (last_check(tokens, line, i) == 1)
                return 0;
    }
    return 1;
}

int    check_pipe(t_token **tokens, char *line, int *i)
{
    if (line[*i + 1] == '|')
    {
        printf("Syntax error: unexpected token '||'\n");
        return 0;
    }
    add_token(tokens, new_token("|", PIPE));
    (*i)++;
    return 1;
}

int check_heredoc(t_token **tokens, char *line, int *i)
{
    if (line[*i] == '>' && line[*i + 1] == '>')
    {
        add_token(tokens, new_token(">>", REDIR_APPEND));
        (*i) += 2;
    }
    else if (line[*i] == '<' && line[*i + 1] == '<')
    {
        add_token(tokens, new_token("<<", HEREDOC));
        (*i) += 2;
    }
    else
    {
        char op[2] = {line[*i], '\0'};
        t_type type;
        if (line[*i] == '>')
            type = REDIR_OUT;
        else
            type = REDIR_IN;
        add_token(tokens, new_token(op, type));
        (*i)++;
    }
    return 1;
}

// int check_quote(t_token **tokens, char *line, int *i)
// {
//     char quote = line[(*i)++];
//     int start = *i;

//     while (line[*i] && line[*i] != quote)
//         (*i)++;
//     while (tokens)
//     {
//         if (quote == '\'')
//             tokens->was_single = 1;
//         else
//             tokens->was_double = 1;
//         tokens = tokens->next;
//     }
//     return 1;
// }

int check_syntax(t_token *tokens)
{
    t_token *current = tokens;

    if (current && current->type == PIPE)
    {
        printf("Syntax error: unexpected '|' \n");
        return 1;
    }
    while (current)
    {
        if (current->type == HEREDOC && current->next && current->next->type == WORD)
            handle_heredocs_range(current);
        if (current->type == PIPE && current->next && current->next->type == PIPE)
        {
            printf("Syntax error: unexpected '||' \n");
            return 1;
        }
        if (current->type == PIPE && current->next == NULL)
        {
            printf("Syntax error: unexpected '|' \n");
            return 1;
        }
        if ((current->type == REDIR_IN || current->type == REDIR_OUT ||
            current->type == REDIR_APPEND || current->type == HEREDOC)
            && (current->next == NULL || current->next->type != WORD))
        {
            printf("Syntax error: missing file after redirection\n");
            return 1;
        }
        if (current && current->type == WORD 
            && current->next  && current->next->type == PIPE 
            && current->next->next && current->next->next->type == PIPE)
        {
            printf("Syntax error: missing file after redirection\n");
            return 1;
        }
        current = current->next;
    }
    return 0;
}
