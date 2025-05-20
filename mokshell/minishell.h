/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:12:38 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/05/20 17:38:02 by ilarhrib         ###   ########.fr       */
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

typedef struct s_exec
{
	char *cmnd_path;
}	t_exec;

typedef struct s_token
{
    char			*value;
    int				was_double;
    int				was_single;
    t_type			type;
    struct s_token	*next;
} t_token;

typedef struct s_exp {
	char *key;
	char *value;
	struct s_exp *next;
}   t_exp;


//@-------------utils----------------------@//
char	**ft_split(char const *s, char c);
void	error(void);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strnstr(const char *hs, const char *n, size_t len);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strcmp(char *s1, char *s2);
char *get_env_value(char *key);
char *get_env2_value(const char *name);
char	***get_env(void);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
int		ft_isalnum(int ch);
char	*ft_substr(char const *novel, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isdigit(int ch);
int		ft_atoi(const char *str);
void	ft_lstadd_back(t_token **lst, t_token *new);
int     ft_isspace(char c);
char    *ft_strcpy(char *dest, const char *src);
char    *ft_strcat(char *dest, const char *src);
char    *ft_strndup(const char *s, size_t n);

//@------------Parsing--------------------@//
void	sigint_handler(int sig);
t_token	*parss(char *line);
void	ft_lstadd_back(t_token **lst, t_token *new);
t_token *new_token(char *valu, t_type type);
void    add_token(t_token **tokens, t_token *new_tok);
char    *type_to_string(t_type type);
int check_syntax(t_token *tokens);
void    expand(t_token *tokens);
void	free_tokens(t_token *tokens);
char *expand_variable(char *line);

//@------------Execution------------------@//
void	execute(char **input, t_token *start, t_token *end, t_exec *exec);
void	cmnd_check(char **input, char **envp, t_token *token, t_exec *exec);
int		builtin_check(char **input, char **envp);
void	execute_pipe_commands(t_token *tokens, t_exec *exec);
void	executor_simple_command(t_token *tokens, t_exec *exec);
void    executor_child_process(t_token *tokens, t_exec *exec);

//~~~~~~~~~~~~Exec_helpers~~~~~~~~~~~~~~~
int		apply_redirections(t_token *start, t_token *end);
void	ft_free_str_array(char **array);
char	*find_command_path(char *cmd, t_exec *exec);
int     contains_pipe_in_tokens(t_token *tokens);
char    **tokens_to_cmd(t_token *start, t_token *end);
void	handle_heredocs(t_token *tokens);
t_exp	*split_env_to_exp(char *env_entry);
void	printf_export_list(void);
t_exp	**get_exp_list(void);
t_exp	*new_exp_node(char *key, char *value);
int     ft_isalpha(int ch);
t_exp	*find_exp(t_exp *list, char *key);
void	add_exp_back(t_exp **lst, t_exp *new);
int     check_valid_key(char *key);
void	export_variable(char *av);
void	init_export_list(void);
void	add_to_env(char *av, char *name, char *value);
int		adjust_env(char *var, char *name);
int		realloc_env(char *var);
int     exist_check(char *env, char *name);
char	**init_env(char **envp);
int     is_builtin(char **input);
void    init_shell(char **envp);
void    read_check(char *readed);
void	built_with_red_check(char **input, char **envp, t_token *tokens);
int		there_is_red(t_token *tokens);
void	leaks_handle(char *readed, t_token *tokens, char **input, t_exec *exec);
void    execute_piped_cmnd(t_token *start, t_token *end, int prev_fd, int fd[2], t_exec *exec);
void    execute_final_command(t_token *start, int prev_fd, t_exec *exec);

//~~~~~~~~~~~~Builtins~~~~~~~~~~~~~~~~~~~
int		shell_echo(char **av);
int		shell_env(char **av,  char **envp);
int		shell_pwd(char **av);
int     shell_export(char **av);
int		shell_unset(char **av);
int		shell_exit(char **av);
void	shell_cd(char **args);

# endif