# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/08 15:01:45 by ilarhrib          #+#    #+#              #
#    Updated: 2025/06/08 15:01:46 by ilarhrib         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = minishell

CC      = cc -Wall -Wextra -Werror #-g -fsanitize=address

CFLAGS  = -I$(HOME)/.local/include

SRCS    = main.c ft_helpers/utils_1.c ft_helpers/utils_2.c ft_helpers/ft_split.c ft_helpers/tmp_env.c \
		builtins/shell_builtins.c execution.c ft_helpers/utils_3.c builtins/shell_builtins_2.c builtins/shell_builtins_3.c \
		ft_helpers/utils_4.c ft_helpers/exec_helper.c ft_helpers/pars_helpers.c \
		ft_helpers/exec_helper_2.c ft_helpers/exec_helper_3.c ft_helpers/exec_helper_4.c \
		parss.c parsing/new_token.c parsing/type.c parsing/expand.c ft_helpers/exec_helper_5.c \
		ft_helpers/exec_helper_6.c ft_helpers/exec_helper_7.c ft_helpers/utils_5.c \
		ft_helpers/parss_helpers_1.c ft_helpers/parss_helpers_2.c ft_helpers/garbage_coll.c \
		ft_helpers/exec_helper_8.c ft_helpers/exec_helper_9.c ft_helpers/exec_helper_10.c \
		parsing/expand_heredoc.c ft_helpers/exec_helper_11.c ft_helpers/parss_hlp.c \
		ft_helpers/parss_checksyn.c parsing/expand_help.c ft_helpers/parss_helper_10.c parsing/expand_helper2.c \
		builtins/shell_builtins_4.c ft_helpers/exec_helper_12.c ft_helpers/exec_helper_13.c

OBJS    = $(SRCS:.c=.o)

HEADER = minishell.h

READLINE_COMPILE = -I$(shell brew --prefix readline)/include

READLINE_LINK = -lreadline -L$(shell brew --prefix readline)/lib

all: $(NAME) stock


$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(READLINE_LINK) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(READLINE_COMPILE) -c $< -o $@ 

stock : $(OBJS)
	mv *.o obj && mv ft_helpers/*.o obj && mv parsing/*.o obj && mv builtins/*.o obj
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) obj/*.o

re: fclean all