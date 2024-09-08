NAME = minishell

SRCS = 	./srcs/main.c		./srcs/input.c \


OBJS = $(SRCS:.c=.o)
CC = cc -Wall -Wextra -Werror
RM = rm -f

$(NAME): $(OBJS)
	@$(CC) -o $(NAME) $(OBJS)

all:$(NAME)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
