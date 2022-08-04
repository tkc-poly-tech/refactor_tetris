CC = gcc
DIR_INCLUDE = ./include
CFLAGS = -Wall -Wextra -Werror -I $(DIR_INCLUDE)
NAME = tetris

DIR_SRC = src
SRCS =	$(DIR_SRC)/tetris.c	\
		$(DIR_SRC)/timer.c	\
		$(DIR_SRC)/score.c	\
		
OBJS = $(SRCS:.c=.o)

all: $(NAME)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -lncurses $(OBJS) -o $@

re:	fclean all
fclean: clean
	$(RM) $(NAME)
clean:
	$(RM) $(OBJS)

.PHONY:	all re fclean clean
