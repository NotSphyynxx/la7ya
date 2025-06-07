/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:37:08 by bael-bad          #+#    #+#             */
/*   Updated: 2025/05/05 17:16:39 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*type_to_string(t_type type)
{
	if (type == WORD) return "WORD";
	if (type == PIPE) return "PIPE";
	if (type == REDIR_IN) return "REDIR_IN";
	if (type == REDIR_OUT) return "REDIR_OUT";
	if (type == REDIR_APPEND) return "REDIR_APPEND";
	if (type == HEREDOC) return "HEREDOC";
	if (type == ENV_VAR) return "ENV_VAR";
	if (type == SINGLE_QUOTE1) return "SINGLE_QUOTE1";
	if (type == DOUBLE_QUOTE1) return "DOUBLE_QUOTE1";
	if (type == SINGLE_QUOTE2) return "SINGLE_QUOTE2";
	if (type == DOUBLE_QUOTE2) return "DOUBLE_QUOTE2";
	return "UNKNOWN";
}