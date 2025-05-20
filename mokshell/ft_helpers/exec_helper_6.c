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

void	leaks_handle(char *readed, t_token *tokens, char **input, t_exec *exec)
{
	if (readed)
		free(readed);
	if (tokens)
		free_tokens(tokens);
	if (input)
		ft_free_str_array(input);
}