/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 23:13:23 by ildaboun          #+#    #+#             */
/*   Updated: 2025/03/07 23:32:02 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_info
{
	int		cmd_nbr;
	int		argcc;
	int		pipe_nbr;
	int		outfile;
	char	**envpp;
	int		psplit;
	int		csplit;
	int		infile;
	int		lst_argm;
	int		a;
	pid_t	proc;
}	t_info;

int		main(int argc, char **argv, char **envp);
char	**get_env(char **env);
int		ft_strlen(const char *str);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	**ft_split(const char *s, char c);
char	*append_access(char **path, char *cmd);
char	*ft_strjoin(const char *s1, const char *s2);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	free_them(char **map);
int		open_file(char *file_name, int file_flag, t_info *info);
void	handle_path(char **path);
void	handle_jpath(char *jpath);
void	kiddo(int **fd, char **argv, t_info *info, int a);
void	dad(int **fd, char **argv, t_info *info, int a);
char	*get_next_line(int fd);
char	*ft_strchr(const char *str, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlenn(const char *s);
void	fork_error(pid_t i);
void	the_doc_thing(char **argv);
void	create_process(char **argv, int **fd, int a, t_info *info);
void	handle_dup(void);
void	set_info(char **argv, int argc, t_info *info, char **envp);
void	set_info2(char **argv, int argc, t_info *info, char **envp);
void	free_fd(int **fd, int rows);
int		**allocate_fd(int rows);
void	pipe_free(t_info *info, int **fd);
void	pipe_failed(void);
void	create_pipes(int a, int **fd);
void	forking(char **argv, t_info *info, int **fd);
void	last_step(char **argv, t_info *info, int **fd);
void	malloc_fd_fail(t_info *info);
void	env_fail(t_info *info, int **fd);
void	set_all(int argc, char **argv, char **envp, t_info *info);
int		ft_strcmp(const char *s1, const char *s2);

#endif
