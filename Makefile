NAME = minishell

SRCS =  ./get_next_line/get_next_line_utils.c ./get_next_line/get_next_line.c \
		./srcs/main.c ./srcs/signal.c ./srcs/exit.c \
		./srcs/double_list.c ./srcs/init.c ./srcs/epure.c \
		./srcs/check.c ./srcs/free.c ./srcs/find.c ./srcs/expand3.c \
		./srcs/input.c ./srcs/error.c ./srcs/parsing.c \
		./srcs/add.c ./srcs/expand.c ./srcs/utils.c ./srcs/expand2.c\
		./srcs/pre_treat.c ./srcs/add1.c ./srcs/epure2.c\
		./srcs/builtin.c ./srcs/builtin2.c  ./srcs/builtin_utils2.c \
		./srcs/execution.c ./srcs/exec_utils.c ./srcs/builtin_utils.c \
		./srcs/exec_utils2.c ./srcs/builtin_utils3.c ./srcs/builtin_utils4.c \
		./srcs/exec_utils3.c ./srcs/parsing2.c ./srcs/signal2.c ./srcs/utils2.c

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
