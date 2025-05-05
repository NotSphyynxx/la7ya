/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:56:49 by bael-bad          #+#    #+#             */
/*   Updated: 2025/05/05 15:57:16 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum
{
    WORD,
    PIPE,
    REDIR_IN,
    REDIR_OUT,
    REDIR_APPEND,
    HEREDOC,
    ENV_VAR,
    SINGLE_QUOTE1,
    SINGLE_QUOTE2,
    DOUBLE_QUOTE1,
    DOUBLE_QUOTE2
}t_type;

typedef struct s_token
{
    char *value;
    t_type type;
    void			*content;
    struct s_token *next;
} t_token;

typedef struct s_parss
{
    char **env;
}t_parss;

void parss(t_parss *envr);
void	ft_lstadd_back(t_token **lst, t_token *new);
char	*ft_strdup(char *s1);
char	**ft_split(char *s, char c);
int	ft_strlen(char *s1);
int	ft_strcmp(char *s1, char *s2);
t_token *new_token(char *valu, t_type type);
void    add_token(t_token **tokens, t_token *new_tok);
char    *type_to_string(t_type type);
int check_syntax(t_token *tokens);
int	ft_strncmp(char *s1, char *s2, int n);
void    expand(t_token *tokens, char **env);
char	*ft_substr(char *s, int start, int len);
char	*ft_strchr(const char *s, int c);

#endif