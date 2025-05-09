/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:12:38 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/05/08 16:06:06 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdbool.h>

typedef enum e_token_type {
    WORD,
    PIPE,
    REDIR_IN,    // <
    REDIR_OUT,   // >
    REDIR_APPEND, // >>
    HEREDOC,     // <<
    ENV_VAR      // $
} t_token_type;

typedef struct s_token {
    char            *value;
    t_token_type    type;
    struct s_token  *next;
} t_token;

typedef struct	s_exec{
	pid_t	chld_pid;
} t_exec;

typedef struct exec_token {
    t_token *strt;
    t_token *crr;
} e_token;

//``````````````Sphynx``````````````````````//
t_token *tokenize_input(const char *input);
void print_tokens(t_token *tokens);
void free_tokens(t_token *tokens);

//@-------------utils----------------------@//
char	**ft_split(char const *s, char c);
void	error(void);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
char	*find_path(char *cmd, char **envp);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strnstr(const char *hs, const char *n, size_t len);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strcmp(char *s1, char *s2);
char	*get_env_value(char *key);
char	***get_env(void);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
int		ft_isalnum(int ch);
char	*ft_substr(char const *novel, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isdigit(int ch);
int		ft_atoi(const char *str);
void	ft_lstadd_back(t_token **lst, t_token *new);


//@------------Parsing--------------------@//
// t_token *new_token(char *valu, t_type type);
// void    add_token(t_token **tokens, t_token *new_tok);
// char    *type_to_string(t_type type);
// int		check_syntax(t_token *tokens);
void	sigint_handler(int sig);
// t_token	*parss(char *input, char **envp);
// void    expand(t_token *tokens, char **env);
// void    free_tokens(t_token *tokens);

//@------------Execution------------------@//
// void	execute(char	**input, t_exec *exec, t_token *tokens);
void	execute(char **input, t_exec *exec, t_token *start, t_token *end);
void	cmnd_check(char **input, char **envp, t_exec *exec, t_token *token);
void	builtin_check(char **input, char **envp);
void    execute_piped_commands(t_token *tokens, t_exec *exec);
// int     handle_redirections(t_token *tokens);
// int		apply_redirections(t_token *start, t_token *end);
//~~~~~~~~~~~~Exec_helpers~~~~~~~~~~~~~~~
int		apply_redirections(t_token *start, t_token *end);
void	ft_free_str_array(char **array);
char	*find_command_path(char *cmd);
int     contains_pipe_in_tokens(t_token *tokens);
char    **tokens_to_cmd(t_token *start, t_token *end);
void	handle_heredocs(t_token *tokens);
//~~~~~~~~~~~~Builtins~~~~~~~~~~~~~~~~~~~
int		shell_echo(char **av);
int		shell_env(char **av,  char **envp);
int		shell_pwd(char **av);
void	shell_cd(char **args);
int		shell_export(char **av);
int		shell_unset(char **av);
int		shell_exit(char **av);

# endif