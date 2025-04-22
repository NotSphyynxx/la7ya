NAME    = minishell
CC      = cc
CFLAGS  = #-Wall -Wextra -Werror 
SRCS    = main.c utils_1.c utils_2.c ft_split.c

OBJS    = $(SRCS:.c=.o)

HEADER = minishell.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

src/%.o: src/%.c $(HEADER)
	$(CC)  $(CFLAGS) -c $< -o $@ 

clean:
	rm -f $(OBJS) $(BS_OBJS)

fclean: clean
	rm -f $(NAME) $(BS_NAME)

re: fclean all