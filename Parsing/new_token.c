/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:15:26 by bael-bad          #+#    #+#             */
/*   Updated: 2025/05/01 18:00:44 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_token *new_token(char *value, t_type type)
{
    t_token *token = malloc(sizeof(t_token));
    if (!token)
        return NULL;
    token->value = ft_strdup(value);
    token->type = type;
    token->content = value;
    token->next = NULL;
    return token;
}

void    add_token(t_token **tokens, t_token *new_tok)
{
    t_token *temp;

    if (!*tokens)
    {
        *tokens = new_tok;
        return ;
    }
    temp = *tokens;
    while (temp->next)
        temp = temp->next;
    temp->next = new_tok;
}