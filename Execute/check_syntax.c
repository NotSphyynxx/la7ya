/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:04:50 by bael-bad          #+#    #+#             */
/*   Updated: 2025/05/05 17:05:02 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
        if (current && current->type == WORD && current->next  
            && current->next->type == DOUBLE_QUOTE1)
        {
            printf("Error: missing closing \"\n");
            return 1;
        }
        if (current && current->type == WORD && current->next  
            && current->next->type == SINGLE_QUOTE1)
        {
            printf("Error: missing closing \'\n");
            return 1;
        }
        current = current->next;
    }
    return 0;
}
