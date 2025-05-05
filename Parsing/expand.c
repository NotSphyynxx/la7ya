/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:14:26 by bael-bad          #+#    #+#             */
/*   Updated: 2025/05/05 16:28:08 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void    expand(t_token *tokens, char **env)
{
    if (!tokens || !tokens->next)
        return ;
    char    *envar = (char *)tokens->content;
    t_token *curr;
    curr = tokens;
    int i;
    if (envar[0] == '$')
    {
        if (envar[1] == '\0')
            return ;
        i = 1;
        while (env[i])
        {
            char var_len = ft_strchr(env[i], '=') - env[i];
            if (ft_strncmp(curr->content + 1, env[i], var_len) == 0 &&
                (int)ft_strlen(curr->content + 1) == var_len)
            {
                free(tokens->content);
                tokens->content = ft_substr(env[i], var_len + 1, ft_strlen(env[i]) - var_len - 1);
                break;
            }
            i++;
        }
    }
    printf("%s\n", tokens->content);
}