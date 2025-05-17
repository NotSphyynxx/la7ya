/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:24:48 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/05/14 14:42:42 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cmnd_check(char **input, char **envp, t_exec *exec, t_token *tokens)
{
    if (tokens)
    {
        if (contains_pipe_in_tokens(tokens))
        {
            execute_piped_commands(tokens, exec);
        }
        else
        {
            char **cmd = tokens_to_cmd(tokens, NULL);
            if (!builtin_check(input, envp))
            {
                printf("1.5\n");
                execute(cmd, exec, tokens, NULL);
                waitpid(exec->chld_pid, NULL, 0);
            }
            ft_free_str_array(cmd);
        }
    }
    else if (input)
    {
        builtin_check(input, envp);
        execute(input, exec, NULL, NULL);
        waitpid(exec->chld_pid, NULL, 0);
    }
}

void execute(char **input, t_exec *exec, t_token *start, t_token *end)
{
    pid_t child_pid;
    char *path;
    child_pid = fork();
    if (child_pid == -1)
    {
        perror("fork error");
        return ;
    }
    if (child_pid == 0)
    {
        if (apply_redirections(start, end) == -1)
            exit(1);
        if(builtin_check(input, *get_env()))
        {
            exit(1);
        }
        path = find_command_path(input[0]);
        if (!path)
        {
            write(STDERR_FILENO, "minishell: command not found\n", 29);
            exit(127);
        }
        exec->chld_pid = child_pid;
        execve(path, input, *get_env());
        perror("execve error");
        exit(1);
    }
}


// ✅ execute_piped_commands: fork for each pipe segment, chain pipes, wait for all
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
                    dup2(prev_fd, STDIN_FILENO);
                dup2(fd[1], STDOUT_FILENO);
                close(fd[0]);
                close(fd[1]);
                if (prev_fd != -1)
                    close(prev_fd);
                char **cmd = tokens_to_cmd(start, curr);
                execute(cmd, exec, start, curr);
                waitpid(exec->chld_pid, NULL, 0);
                ft_free_str_array(cmd);
                exit(0);
            }
            close(fd[1]);
            if (prev_fd != -1)
                close(prev_fd);
            prev_fd = fd[0];
            start = curr->next;
        }
        curr = curr->next;
    }

    // Final command (after last pipe)
    child_pid = fork();
    if (child_pid == 0)
    {
        if (prev_fd != -1)
            dup2(prev_fd, STDIN_FILENO);
        if (prev_fd != -1)
            close(prev_fd);
        char **cmd = tokens_to_cmd(start, NULL);
        execute(cmd, exec, start, NULL);
        waitpid(exec->chld_pid, NULL, 0);
        ft_free_str_array(cmd);
        exit(0);
    }
    if (prev_fd != -1)
        close(prev_fd);

    while (wait(NULL) > 0);
}



// ✅ apply_redirections: applies redirections from start up to end
int apply_redirections(t_token *start, t_token *end)
{
    t_token *curr = start;
    int fd;

    while (curr && curr != end)
    {
        if (curr->type == REDIR_OUT)
        {
            fd = open(curr->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
                return (perror("open >"), -1);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (curr->type == REDIR_APPEND)
        {
            fd = open(curr->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0)
                return (perror("open >>"), -1);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (curr->type == REDIR_IN)
        {
            fd = open(curr->next->value, O_RDONLY);
            if (fd < 0)
                return (perror("open <"), -1);
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        curr = curr->next;
    }
    return (0);
}
