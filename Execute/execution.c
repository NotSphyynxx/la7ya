
#include "minishell.h"

void	cmnd_check(char **input, char **envp, t_exec *exec, t_token *tokens)
{
    if (tokens)
    {
        if (contains_pipe_in_tokens(tokens))
            execute_piped_commands(tokens, exec);
        else
        {
            char **cmd = tokens_to_cmd(tokens, NULL);
            execute(cmd, exec);
            waitpid(exec->chld_pid, NULL, 0);
            ft_free_str_array(cmd);
        }
    }
    else if (input)
    {
        builtin_check(input, envp);
        execute(input, exec);
        waitpid(exec->chld_pid, NULL, 0);
    }
}


void	execute(char	**input, t_exec *exec)
{
	pid_t	child_pid;
	char		*path;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork error");
		return ;
	}
	if (child_pid == 0)
	{
		path = find_command_path(input[0]);
		if (!path)
		{
			write(STDERR_FILENO, "minishell: command not found\n", 29);
			exit(127);
		}
		exec->chld_pid = child_pid;
		if (execve(path, input, *get_env()) == -1)
		{
			perror("execve error");
            exit(1);
		}
	}
}

void execute_piped_commands(t_token *tokens, t_exec *exec)
{
    t_token *curr = tokens;
    t_token *start = tokens;
    pid_t child_pid;
    int fd[2];
    int prev_fd = -1;

    while (curr)
    {
        if (curr->type == PIPE)
        {
            pipe(fd);
            child_pid = fork();
            if (child_pid == 0)
            {
                if (prev_fd != -1)
                {
                    dup2(prev_fd, STDIN_FILENO);
                    close(prev_fd);
                }
                dup2(fd[1], STDOUT_FILENO);
                close(fd[0]);
                close(fd[1]);

                char **cmd = tokens_to_cmd(start, curr);
                execute(cmd, exec);
                waitpid(exec->chld_pid, NULL, 0);
                ft_free_str_array(cmd);
                exit(0);
            }
            else
            {
                close(fd[1]);
                if (prev_fd != -1)
                    close(prev_fd);
                prev_fd = fd[0];
            }
            start = curr->next;
        }
        curr = curr->next;
    }

    child_pid = fork();
    if (child_pid == 0)
    {
        if (prev_fd != -1)
        {
            dup2(prev_fd, STDIN_FILENO);
            close(prev_fd);
        }
        char **cmd = tokens_to_cmd(start, NULL);
        execute(cmd, exec);
        waitpid(exec->chld_pid, NULL, 0);
        ft_free_str_array(cmd);
        exit(0);
    }
    else
    {
        if (prev_fd != -1)
            close(prev_fd);
    }

    while (wait(NULL) > 0); // wait for all children
}
