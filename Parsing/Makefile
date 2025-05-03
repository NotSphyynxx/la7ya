#------------------------------Source Files------------------------------------#
SRC = main.c parss.c lstadd.c ft_split.c ft_strlen.c ft_strcmp.c new_token.c ft_strdup.c \
		type.c check_syntax.c expand.c

#------------------------------Object Files------------------------------------#
OBJ = $(SRC:.c=.o)

#------------------------------Compiler and Flags------------------------------#
CC = cc
CFLAGS = -Wall -Wextra -Werror

#------------------------------Includes and Executables------------------------#
NAME = minishell

READLINE_COMPILE = -I$(shell brew --prefix readline)/include
READLINE_LINK = -lreadline -L$(shell brew --prefix readline)/lib

#------------------------------Rules-------------------------------------------#
all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(READLINE_LINK)

%.o: %.c includes/minishell.h
	@$(CC) $(CFLAGS) $(READLINE_COMPILE) -c $< -o $@
	@echo █▀▄▀█ ░▀░ █▀▀▄ ░▀░ █░░█ █▀▀ █░░ █░░
	@echo █░▀░█ ▀█▀ █░░█ ▀█▀ █▀▀█ █▀▀ █░░ █░░
	@echo ▀░░░▀ ▀▀▀ ▀░░▀ ▀▀▀ ▀░░▀ ▀▀▀ ▀▀▀ ▀▀▀

#------------------------------Clean-------------------------------------------#
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

#------------------------------Rebuild-----------------------------------------#
re: fclean all
