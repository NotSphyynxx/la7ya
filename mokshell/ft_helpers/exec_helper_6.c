/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper_6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:33:05 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/05/20 17:39:00 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	leaks_handle(char *readed, t_token *tokens)
{
	if (readed)
		free(readed);
	if (tokens)
		free_tokens(tokens);
}

int apply_redirections(t_token *start, t_token *end)
{
    t_token *curr = start;
    int      fd;
    t_token *file_tok;

    while (curr && curr != end)
    {
        if (curr->type == REDIR_IN)
        {
            file_tok = curr->next;
            // 1) Missing target or empty value
            if (!file_tok || !file_tok->value || file_tok->value[0] == '\0')
            {
                write(STDERR_FILENO, "minishell: ambiguous redirect\n", 30);
                return (-1);
            }
            // 2) Marked ambiguous during expand
            if (file_tok->ambigious)
            {
                write(STDERR_FILENO, "minishell: ambiguous redirect\n", 30);
                return (-1);
            }
            fd = open(curr->next->value, O_RDONLY);
            if (fd < 0)
                return (perror("open <"), -1);

            // if it's one of our heredoc files, remove it now
            if (ft_strncmp(curr->next->value,
                           "/tmp/.heredoc_tmp_", 18) == 0)
            {
                unlink(curr->next->value);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        else if (curr->type == REDIR_OUT)
        {
            file_tok = curr->next;
            // 1) Missing target or empty value
            if (!file_tok || !file_tok->value || file_tok->value[0] == '\0')
            {
                write(STDERR_FILENO, "minishell: ambiguous redirect\n", 30);
                return (-1);
            }
            // 2) Marked ambiguous during expand
            if (file_tok->ambigious)
            {
                write(STDERR_FILENO, "minishell: ambiguous redirect\n", 30);
                return (-1);
            }
            fd = open(curr->next->value,
                      O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
                return (perror("open >"), -1);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (curr->type == REDIR_APPEND)
        {
            file_tok = curr->next;
            // 1) Missing target or empty value
            if (!file_tok || !file_tok->value || file_tok->value[0] == '\0')
            {
                write(STDERR_FILENO, "minishell: ambiguous redirect\n", 30);
                return (-1);
            }
            // 2) Marked ambiguous during expand
            if (file_tok->ambigious)
            {
                write(STDERR_FILENO, "minishell: ambiguous redirect\n", 30);
                return (-1);
            }
            fd = open(curr->next->value,
                      O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0)
                return (perror("open >>"), -1);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        curr = curr->next;
    }
    return (0);
}

void    execute_piped_cmnd(t_token *start, t_token *end, int prev_fd, int fd[2], t_exec *exec)
{
    pid_t child_pid;

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
        char **cmd = tokens_to_cmd(start, end);
        execute(cmd, start, end, exec);
        ft_free_str_array(cmd);
        exit(0);
    }
}

void execute_final_command(t_token *start, int prev_fd, t_exec *exec)
{
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == 0)
    {
        if (prev_fd != -1)
            dup2(prev_fd, STDIN_FILENO);
        if (prev_fd != -1)
            close(prev_fd);
        char **cmd = tokens_to_cmd(start, NULL);
        if (!cmd)
            exit(0);
        execute(cmd, start, NULL, exec);
        ft_free_str_array(cmd);
        exit(0);
    }
}

void executor_child_process(t_token *tokens, t_exec *exec)
{
    char **cmd;
    char *path;

    handle_heredocs_range(tokens);
    if (apply_redirections(tokens, NULL) == -1)
        exit(1);
    cmd = tokens_to_cmd(tokens, NULL);
    if (!cmd)
        exit (0);
    if (builtin_check(cmd, *get_env()))
    {
        ft_free_str_array(cmd);
        exit(0);
    }
    path = find_command_path(cmd[0], exec);
    if (!path)
    {
        write(2, "minishell: command not found\n", 29);
        ft_free_str_array(cmd);
        exit(127);
    }
    execve(path, cmd, *get_env());
    perror("execve failed");
    ft_free_str_array(cmd);
    exit(1);
}
