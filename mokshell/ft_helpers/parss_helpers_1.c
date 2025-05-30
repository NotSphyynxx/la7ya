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

static void	handle_heredoc_child(t_token *curr, char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("heredoc tmp file error");
		exit(1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, curr->next->value) == 0)
		{
			free(line);
			break;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
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
        // printf("1\n");
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

int check_quote(t_token **tokens, char *line, int *i)
{
    char quote = line[(*i)++];
    int start = *i;

    while (line[*i] && line[*i] != quote)
        (*i)++;

    if (!line[*i])
    {
        printf("Syntax error: unclosed quote\n");
        return 0;
    }
    // Include the quotes when storing the value
    int full_len = *i - start + 2; // +2 for both quotes
    char *full_quoted = ft_substr(line, start - 1, full_len);

    t_token *new_tok = new_token(full_quoted, WORD);
    if (quote == '\'')
        new_tok->was_single = 1;
    else
        new_tok->was_double = 1;
    add_token(tokens, new_tok);
    free(full_quoted);
    (*i)++; // skip closing quote
    return 1;
}

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
        {
            handle_heredocs_range(current);
            // printf("2\n");
        }
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
