# Makefile for Taquin

NAME		=	taquin

SRC		=	./src/main.cpp			\
			./src/AStar.cpp			\
			./src/Node.cpp			\
			./src/LinearConflict.cpp	\
			./src/Manhattan9.cpp		\
			./src/MisplacedTiles.cpp	\
			./src/Parser.cpp		\
			./src/OutOf.cpp

OBJ		=	$(SRC:.cpp=.o)

RM		=	rm -f

CC		=	g++

INCLUDE		=	./include

CPPFLAGS	+=	-O3 -W -Wall -I $(INCLUDE)

#

$(OBJ)		:	$(SRC)

all		:	$(NAME)

$(NAME)		:	$(OBJ)
			$(CC) $(OBJ) -o $(NAME)

clean		:
			$(RM) ./src/*.o

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all
