NAME    = minishell

CC      = cc #-g -fsanitize=address

CFLAGS  = -I$(HOME)/.local/include

SRCS    = main.c ft_helpers/utils_1.c ft_helpers/utils_2.c ft_helpers/ft_split.c ft_helpers/tmp_env.c \
		shell_builtins.c execution.c ft_helpers/utils_3.c shell_builtins_2.c shell_builtins_3.c \
		ft_helpers/utils_4.c ft_helpers/exec_helper.c sphynx.c ft_helpers/pars_helpers.c \
		ft_helpers/exec_helper_2.c ft_helpers/exec_helper_3.c ft_helpers/exec_helper_4.c

OBJS    = $(SRCS:.c=.o)

HEADER = minishell.h

# READLINE_COMPILE = -I$(shell brew --prefix readline)/include

# READLINE_LINK = -lreadline -L$(shell brew --prefix readline)/lib

all: $(NAME) stock


$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ 

stock : $(OBJS)
	mv *.o obj && mv ft_helpers/*.o obj 
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) obj/*.o

re: fclean all