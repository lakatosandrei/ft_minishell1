NAME = ft_minishell1

CC = gcc

FLAGS = -Wall -Wextra -Werror -g -o

LIBRARY = -L ./libft/ -lft

SRCS = main.c get_next_line.c ft_setenv.c ft_getcom.c

OBJ = $(SRCS:.c=.o)

CREATE = make -C ./libft

all:
	$(CREATE)
	$(CC) $(FLAGS) $(NAME) $(SRCS) $(LIBRARY)

RM = rm -f

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
