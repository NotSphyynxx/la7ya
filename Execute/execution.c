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
        handle_heredocs(tokens);
        if (contains_pipe_in_tokens(tokens))
        {
            printf("contains pipe.....\n");
            execute_piped_commands(tokens, exec);
        }
        else
        {
            if (!builtin_check(input, envp))
            {
                printf("no contains pipe.....\n");
                executor_simple_command(tokens, exec);
            }
        }
    }
}

void execute(char **input, t_exec *exec, t_token *start, t_token *end)
{
    char *path;

    if (apply_redirections(start, end) == -1)
        exit(1);

    if (builtin_check(input, *get_env()))
    {
        printf("used a builtin\n");
        exit(0);
    }

    path = find_command_path(input[0]);
    if (!path)
    {
        write(STDERR_FILENO, "minishell: command not found\n", 29);
        exit(127);
    }

    printf("about to execve: %s\n", path);
    execve(path, input, *get_env());
    perror("execve failed");
    exit(126);
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
                printf("here in child == 0\n");
                if (prev_fd != -1)
                    dup2(prev_fd, STDIN_FILENO);
                dup2(fd[1], STDOUT_FILENO);
                close(fd[0]);
                close(fd[1]);
                if (prev_fd != -1)
                    close(prev_fd);
                printf("about to execute 1\n");
                char **cmd = tokens_to_cmd(start, curr);
                execute(cmd, exec, start, curr);
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
        printf("about to execute 2\n");
        execute(cmd, exec, start, NULL);
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
            // If it's the heredoc temp file, delete it now
            if (ft_strcmp(curr->next->value, "/tmp/.heredoc_tmp") == 0)
                unlink(curr->next->value);

            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        curr = curr->next;
    }
    return (0);
}

void executor_simple_command(t_token *tokens, t_exec *exec)
{
    pid_t pid;
    char **cmd;
    char *path;

    pid = fork();
    if (pid == -1)
    {
        perror("fork error");
        return ;
    }
    if (pid == 0)
    {
        if (apply_redirections(tokens, NULL) == -1)
            return ;
        cmd = tokens_to_cmd(tokens, NULL);
        if (builtin_check(cmd, *get_env()))
        {
            ft_free_str_array(cmd);
            exit(0);
        }
        path = find_command_path(cmd[0]);
        if (!path)
        {
            write(2, "minishell: command not found\n", 29);
            ft_free_str_array(cmd);
            exit(127);
        }
        printf("executing cmnd in this path -> %s\n", path);
        execve(path, cmd, *get_env());
        printf("1\n");
        perror("execve failed");
        ft_free_str_array(cmd);
        exit(1);
    }
    waitpid(pid, NULL, 0);
}
