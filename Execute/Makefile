NAME    = minishell
CC      = cc
CFLAGS  = -I$(HOME)/.local/include
LDFLAS	= -L$(HOME)/.local/lib
SRCS    = main.c ft_helpers/utils_1.c ft_helpers/utils_2.c ft_helpers/ft_split.c ft_helpers/tmp_env.c shell_builtins.c execution.c

OBJS    = $(SRCS:.c=.o)

HEADER = minishell.h

all: $(NAME) stock

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAS) $(OBJS) -lreadline -lncurses -o $(NAME)

src/%.o: src/%.c $(HEADER)
	$(CC)  $(CFLAGS) -c $< -o $@ 

stock : $(OBJS)
	mkdir obj
	mv *.o obj && mv ft_helpers/*.o obj 
clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf $(NAME) obj

re: fclean all