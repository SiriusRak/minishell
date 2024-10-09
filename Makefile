NAME = minishell

SRCS = 	./srcs/print_all.c \
		./srcs/main.c ./srcs/input.c ./srcs/signal.c \
		./srcs/double_list.c ./srcs/exit.c ./srcs/heredoc.c \
		./srcs/check.c ./srcs/init.c ./srcs/free_loop.c \
		./srcs/debug.c 

LIB = libft

OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror -lreadline -g
RM = rm -f

$(NAME): $(OBJS)
	@make -s bonus -C $(LIB)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -Llibft -lft

all:$(NAME)

clean:
	@$(RM) $(OBJS)
	@make -s clean -C $(LIB) 

fclean: clean
	@$(RM) $(NAME)
	@make -s fclean -C $(LIB)

re: fclean all
