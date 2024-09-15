NAME = minishell

SRCS = 	./srcs/main.c ./srcs/input.c ./srcs/signal.c \
		./srcs/double_list.c

LIB = libft

OBJS = $(SRCS:.c=.o)
FLAGS = -Wall -Wextra -Werror -lreadline
RM = rm -f

$(NAME): $(OBJS)
	@make bonus -s -C $(LIB)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) -Llibft -lft

all:$(NAME)

clean:
	@$(RM) $(OBJS)
	@make clean -C $(LIB) 

fclean: clean
	@$(RM) $(NAME)

re: fclean all
