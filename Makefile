NAME = minishell

SRCS = 	./srcs/main.c ./srcs/input.c ./srcs/signal.c \
		./srcs/double_list.c ./srcs/builtin.c ./srcs/builtin2.c ./srcs/utils.c \
		./srcs/execution.c ./srcs/exec_utils.c

LIB = libft

OBJS = $(SRCS:.c=.o)
FLAGS = -Wall -Wextra -Werror -g -lreadline 
RM = rm -f

$(NAME): $(OBJS)
	@make -s bonus -C $(LIB)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) -Llibft -lft

all:$(NAME)

clean:
	@$(RM) $(OBJS)
	@make -s clean -C $(LIB) 

fclean: clean
	@$(RM) $(NAME)
	@make -s fclean -C $(LIB)

re: fclean all
