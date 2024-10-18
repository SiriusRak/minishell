NAME = minishell

SRCS = 	./srcs/print_all.c \
		./srcs/main.c ./srcs/signal.c ./srcs/exit.c \
		./srcs/double_list.c ./srcs/init.c ./srcs/epure.c \
		./srcs/check.c ./srcs/free.c ./srcs/find.c \
		./srcs/input.c ./srcs/error.c ./srcs/parsing.c \
		./srcs/add.c \

LIB = libft

OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline
CC = cc
RM = rm -f

$(NAME): $(OBJS)
	@make -s bonus -C $(LIB)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -Llibft -lft $(LDFLAGS)

all: $(NAME)

clean:
	@$(RM) $(OBJS)
	@make -s clean -C $(LIB) 

fclean: clean
	@$(RM) $(NAME)
	@make -s fclean -C $(LIB)

re: fclean all
