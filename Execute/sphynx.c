/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphynx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:15:50 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/05/13 17:47:09 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool is_quote(char c) {
    return c == '\'' || c == '"';
}

// Helper function to get the length until space or special character
static size_t get_word_length(const char *str) {
    size_t len = 0;
    bool in_quote = false;
    char quote_char = 0;

    while (str[len]) {
        if (is_quote(str[len])) {
            if (!in_quote) {
                quote_char = str[len];
                in_quote = true;
            } else if (str[len] == quote_char) {
                in_quote = false;
            }
        } else if (!in_quote && (str[len] == ' ' || str[len] == '|' || 
                  str[len] == '<' || str[len] == '>')) {
            break;
        }
        len++;
    }
    return len;
}

// Helper function to identify special tokens
static t_token_type get_special_type(const char *str) {
    if (str[0] == '|') return PIPE;
    if (str[0] == '<') {
        if (str[1] == '<') return HEREDOC;
        return REDIR_IN;
    }
    if (str[0] == '>') {
        if (str[1] == '>') return REDIR_APPEND;
        return REDIR_OUT;
    }
    if (str[0] == '$') return ENV_VAR;
    return WORD;
}

// Main tokenization function
t_token *tokenize_input(const char *input) {
    t_token *head = NULL;
    t_token **current = &head;
    const char *ptr = input;

    while (*ptr) {
        // Skip whitespace
        while (*ptr == ' ') ptr++;
        if (!*ptr) break;

        // Determine token type and length
        t_token_type type = get_special_type(ptr);
        size_t len = (type == WORD) ? get_word_length(ptr) : 
                     (type == HEREDOC || type == REDIR_APPEND) ? 2 : 1;

        // Handle quotes for WORD tokens
        if (type == WORD && is_quote(*ptr)) {
            char quote = *ptr;
            const char *end = strchr(ptr + 1, quote);
            if (end) {
                len = end - ptr + 1;
            }
        }

        // Create new token
        t_token *new_token = malloc(sizeof(t_token));
        if (!new_token) {
            // Free all tokens on allocation failure
            free_tokens(head);
            return NULL;
        }

        new_token->value = strndup(ptr, len);
        new_token->type = type;
        new_token->next = NULL;

        // Add to list
        *current = new_token;
        current = &(*current)->next;

        // Move pointer forward
        ptr += len;
    }

    return head;
}

void print_tokens(t_token *tokens) {
    const char *type_names[] = {
        "WORD", "PIPE", "REDIR_IN", "REDIR_OUT", 
        "REDIR_APPEND", "HEREDOC", "ENV_VAR"
    };

    while (tokens) {
        // printf("Token: type=%s, value='%s'\n", 
        //       type_names[tokens->type], tokens->value);
        tokens = tokens->next;
    }
}

void free_tokens(t_token *tokens) {
    while (tokens) {
        t_token *next = tokens->next;
        free(tokens->value);
        free(tokens);
        tokens = next;
    }
}

void collect_redirections(t_token *tokens, t_redir **in, t_redir **out) {
    t_token *curr = tokens;
    while (curr) {
        if (curr->type == REDIR_IN || curr->type == HEREDOC) {
            t_redir *new = malloc(sizeof(t_redir));
            new->filename = curr->next ? strdup(curr->next->value) : NULL;
            new->type = curr->type;
            new->next = *in;
            *in = new;
            curr = curr->next; // Skip filename token
        }
        else if (curr->type == REDIR_OUT || curr->type == REDIR_APPEND) {
            t_redir *new = malloc(sizeof(t_redir));
            new->filename = curr->next ? strdup(curr->next->value) : NULL;
            new->type = curr->type;
            new->next = *out;
            *out = new;
            curr = curr->next; // Skip filename token
        }
        curr = curr->next;
    }
}

void setup_redirections(t_redir *in, t_redir *out) {
    // Handle input redirections (last one wins)
    while (in) {
        int fd = open(in->filename, O_RDONLY);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
        in = in->next;
    }

    // Handle output redirections (process in reverse order)
    t_redir *last_out = NULL;
    t_redir *tmp = out;
    while (tmp) {
        last_out = tmp;  // Find the last one
        tmp = tmp->next;
    }

    if (last_out) {
        int flags = O_WRONLY | O_CREAT;
        if (last_out->type == REDIR_APPEND)
            flags |= O_APPEND;
        else
            flags |= O_TRUNC;

        int fd = open(last_out->filename, flags, 0644);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
}

void free_redirections(t_redir *list) {
    while (list) {
        t_redir *next = list->next;
        free(list->filename);
        free(list);
        list = next;
    }
}

bool is_simple_builtin_tokens(t_token *tokens)
{
    if (!tokens || tokens->type != WORD)
        return false;

    if (ft_strcmp(tokens->value, "echo") == 0 ||
        ft_strcmp(tokens->value, "pwd") == 0 ||
        ft_strcmp(tokens->value, "exit") == 0 ||
        ft_strcmp(tokens->value, "cd") == 0 ||
        ft_strcmp(tokens->value, "export") == 0 ||
        ft_strcmp(tokens->value, "unset") == 0)
        return true;

    return false;
}


bool contains_redirection(t_token *tokens)
{
    while (tokens)
    {
        if (tokens->type == REDIR_IN ||
            tokens->type == REDIR_OUT ||
            tokens->type == REDIR_APPEND ||
            tokens->type == HEREDOC)
            return (true);
        tokens = tokens->next;
    }
    return (false);
}

char **tokens_to_cmd_without_redirs(t_token *tokens)
{
    int count = 0;
    t_token *tmp = tokens;

    while (tmp)
    {
        if (tmp->type == WORD)
            count++;
        tmp = tmp->next;
    }

    char **cmd = malloc(sizeof(char *) * (count + 1));
    if (!cmd)
        return NULL;

    int i = 0;
    tmp = tokens;
    while (tmp)
    {
        if (tmp->type == WORD)
            cmd[i++] = ft_strdup(tmp->value);
        tmp = tmp->next;
    }
    cmd[i] = NULL;
    return cmd;
}
