CC = gcc
DIR_INCLUDE = ./include
CFLAGS = -Wall -Wextra -Werror -lncurses -I $(DIR_INCLUDE)

NAME = tetris

DIR_SRC = src
SRCS =	$(DIR_SRC)/tetris.c \

all: $(NAME)
$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@

re:	fclean all
fclean: clean
	$(RM) $(NAME)
clean:
#	$(RM) $(OBJS)

.PHONY:	$(NAME) all re fclean clean