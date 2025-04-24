/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ildaboun <ildaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 23:13:23 by ildaboun          #+#    #+#             */
/*   Updated: 2025/03/07 23:31:29 by ildaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

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
int		open_file(char *file_name, int file_flag, int fd[2]);
void	handle_path(char **path);
void	handle_jpath(char *jpath);
void	kiddo(int fd[2], char **argv, char **envp);
void	dad(int fd[2], char **argv, char **envp);
void	handle_dup(void);
void	fork_fail(int fd[2]);
void	pipe_fail(void);
void	env_fail(char **envp, int file, int fd[2]);
char	*ft_strchr(const char *str, int c);
void	fail(int file, int fd[2]);

#endif
