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

t_token *parss(char *input, char **envp) {
    t_token *tokens = tokenize_input(input);
    if (!tokens) return NULL;
    
    // First pass: identify standalone variables as WORD tokens
    t_token *current = tokens;
    while (current) {
        if (current->value[0] == '$' && current->type != ENV_VAR) {
            current->type = WORD; // Treat as word to be expanded
        }
        current = current->next;
    }
    
    // Expand environment variables
    expand_tokens(tokens, envp);
    
    return tokens;
}

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

// Main expansion function for tokens
// Helper function to expand a single environment variable
void expand_env_var(t_token *token, char **envp) {
    if (!token || token->type != WORD || !strchr(token->value, '$'))
        return;

    char *result = malloc(1);
    result[0] = '\0';
    char *ptr = token->value;

    while (*ptr) {
        if (*ptr == '$' && (ptr == token->value || ptr[-1] != '\\')) {
            ptr++; // Skip $
            char var_name[256];
            int i = 0;
            
            // Handle special case $?
            if (*ptr == '?') {
                char *exit_status = ft_itoa(g_exit_status);
                char *new_result = ft_strjoin(result, exit_status);
                free(result);
                free(exit_status);
                result = new_result;
                ptr++;
                continue;
            }
            
            // Extract variable name
            while (*ptr && (ft_isalnum(*ptr) || *ptr == '_')) {
                var_name[i++] = *ptr++;
            }
            var_name[i] = '\0';
            
            // Find in environment
            char *var_value = NULL;
            for (int j = 0; envp[j]; j++) {
                if (ft_strncmp(envp[j], var_name, i) == 0 && envp[j][i] == '=') {
                    var_value = envp[j] + i + 1;
                    break;
                }
            }
            
            if (var_value) {
                char *new_result = ft_strjoin(result, var_value);
                free(result);
                result = new_result;
            }
        } else {
            // Append regular character
            char ch[2] = {*ptr++, '\0'};
            char *new_result = ft_strjoin(result, ch);
            free(result);
            result = new_result;
        }
    }

    // Replace the token's value with expanded version
    free(token->value);
    token->value = result;
}

void expand_tokens(t_token *tokens, char **envp) {
    t_token *current = tokens;
    
    while (current) {
        expand_env_var(current, envp);
        current = current->next;
    }
}

void free_token(t_token *token) {
    if (!token) return;
    free(token->value);
    free(token);
}

void free_tokens(t_token *tokens) {
    t_token *current = tokens;
    t_token *next;
    
    while (current) {
        next = current->next;
        free_token(current);
        current = next;
    }
}

#include <stdlib.h>

static int	ft_numlen(int n)
{
	int	len;

	len = 1;
	while (n / 10)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				len;
	unsigned int	nb;

	len = ft_numlen(n);
	if (n < 0)
	{
		nb = -n;
		len++; // for the minus sign
	}
	else
		nb = n;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = (nb % 10) + '0';
		nb /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
