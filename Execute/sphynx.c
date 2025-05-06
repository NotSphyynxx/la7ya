/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphynx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:15:50 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/05/06 16:29:11 by ilarhrib         ###   ########.fr       */
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