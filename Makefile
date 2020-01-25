##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## A Makefile to compile mysh (minishell1)
##

NAME	=	mysh

SRC	=	source/main.c\
		source/env_chained_list.c\
		source/main_loop.c\
		source/launch_cd.c\
		source/env_related_builtins.c\
		source/my_tools.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	+=	-Wall -Wextra -Iinclude

NAME_TESTS	=	tests_mysh

SRC_TESTS	=

OBJ_TESTS	=	$(SRC_TESTS:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
			gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
		rm -f $(OBJ)
		rm -f $(OBJ_TESTS)

fclean:	clean
		rm -f $(NAME)
		rm -f $(NAME_TESTS)
		rm -f *.gcno
		rm -f *.gcda

re:	fclean all

tests_run:	$(SRC_TESTS)
			rm -f *.gcno
			rm -f *.gcda
			gcc -o $(NAME_TESTS) $(SRC_TESTS) $(CFLAGS) --coverage -lcriterion
			./$(NAME_TESTS)