
#include "minishell.h"

void	cmnd_check(char **input, char **envp, t_exec *exec)
{
	builtin_check(input, envp);
	if (contains_pipe(input)){
		execute_piped_commands(input, exec);
	}
	else
	{
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

void execute_piped_commands(char **input, t_exec *exec) {
    int	fd[2], prev_fd = -1, i = 0;
	pid_t	child_pid;

	while (input[i])
	{
		if (ft_strcmp(input[i], "|") == 0)
		{
			input[i] = NULL;
            if (pipe(fd) == -1) {
                perror("pipe error");
				return;
			}
			
			child_pid = fork();
			if (child_pid == -1) {
                perror("fork error");
                return;
            }

            if (child_pid == 0)
			{
                dup2(fd[1], STDOUT_FILENO);
                close(fd[0]);
                if (prev_fd != -1)
				{
                    dup2(prev_fd, STDIN_FILENO);
                    close(prev_fd);
                }
                execute(split_command(input, 0, i), exec);
				waitpid(exec->chld_pid, NULL, 0);
                exit(0); // Child exits after execve
            }
			else
			{
                close(fd[1]); // Close write end of pipe in parent
                if (prev_fd != -1) close(prev_fd); // Close previous pipe
                prev_fd = fd[0]; // Store read end for next process
            }
            input += i + 1;
            i = 0;
        }
		else
		{
            i++;
        }
    }
    if (*input)
	{
        child_pid = fork();
        if (child_pid == -1)
		{
            perror("fork error");
            return;
        }
        if (child_pid == 0)
		{
            if (prev_fd != -1)
			{
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            execute(input, exec);
			waitpid(exec->chld_pid, NULL, 0);
            exit(0);
        }
		else
		{
            if (prev_fd != -1) close(prev_fd);
        }
    }
    waitpid(child_pid, NULL, 0);
}
