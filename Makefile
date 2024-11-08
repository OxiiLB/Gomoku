##
## EPITECH PROJECT, 2024
## makefile
## File description:
## makefile
##

SRC			=	main.cpp		\


FILE		=	command.cpp		\
				system.cpp		\

TEST		=	test.cpp

DIR_SRC		=	$(addprefix Src/, $(SRC))
DIR_FILE	=	$(addprefix Src/, $(FILE))
DIR_TESTS	=	$(addprefix Tests/, $(TEST))

OBJ_SRC		=	$(DIR_SRC:.cpp=.o)
OBJ_FILE	=	$(DIR_FILE:.cpp=.o)
OBJ			=	$(OBJ_SRC) $(OBJ_FILE)

NAME		=	pbrain-gomoku-ai

CPPFLAGS	=	-I./Include/ -I./Include/Interface

WFLAGS		=	-W -Wall -Wextra -Werror

LCRITER		= --coverage -lcriterion

$(NAME): $(OBJ)
	g++ -o $@ $^ $(CPPFLAGS) $(WFLAGS)

debug: $(OBJ_SRC)
	g++ -o $(NAME) $^ $(CPPFLAGS) $(WFLAGS) -ggdb3

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -rf unit_tests/

re: fclean $(NAME)

unit_tests:	fclean
	mkdir unit_tests
	g++ -o unit_tests/unit_tests $(DIR_SRC) $(DIR_TESTS) $(CPPFLAGS) \
	$(WFLAGS) $(LCRITER)

tests_run:	unit_tests
	./unit_tests/unit_tests

.PHONY: all clean fclean re unit_tests tests_run
