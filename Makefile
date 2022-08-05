CC = gcc
DIR_INCLUDE = ./include
CFLAGS = -Wall -Wextra -Werror -I $(DIR_INCLUDE)
NAME = tetris

DIR_SRC = src
SRCS =	$(DIR_SRC)/main.c	\
		$(DIR_SRC)/timer.c	\
		$(DIR_SRC)/score.c	\
		$(DIR_SRC)/piece.c	\
		$(DIR_SRC)/piece_template.c	\
		$(DIR_SRC)/controll.c	\
		$(DIR_SRC)/validation.c	\
		$(DIR_SRC)/view.c	\
		$(DIR_SRC)/table.c	\
		
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
