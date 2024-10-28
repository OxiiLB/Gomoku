##
## EPITECH PROJECT, 2024
## makefile
## File description:
## makefile
##

SRC			=	main.cpp

TEST		=	test.cpp

DIR_SRC		=	$(addprefix src/, $(SRC))
DIR_TESTS	=	$(addprefix tests/, $(TEST))

OBJ_SRC		=	$(DIR_SRC:.cpp=.o)
OBJ			=	$(OBJ_SRC)

NAME		=	project

CPPFLAGS	=	-I./includes/

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
