# Makefile for Taquin

NAME		=	taquin

SRC		=	./src/main.c		\
			./src/astar.c		\
			./src/lists.c		\
			./src/arguments.c	\
			./src/heuristic.c	\
			./src/display.c		\
			./src/tools.c		\
			./src/alloc.c		\

OBJ		=	$(SRC:.c=.o)

RM		=	rm -f

CC		=	gcc

INCLUDE		=	./include

CFLAGS		+=	-W -Wall -I $(INCLUDE)

#

all		:	$(NAME)

$(NAME)		:	$(OBJ)
			$(CC) $(OBJ) -o $(NAME)

clean		:
			$(RM) ./src/*.o

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all
