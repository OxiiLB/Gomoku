##
## EPITECH PROJECT, 2024
## makefile
## File description:
## makefile
##

SRC			=	main.cpp		\


FILE		=	command.cpp				\
				system.cpp				\
				defenseAlgorithm.cpp	\
				log.cpp					\
				Brain/game_logic.cpp	\
				Brain/mcts.cpp	\
				Brain/node.cpp	\

TEST		=	test.cpp

DIR_SRC		=	$(addprefix Src/, $(SRC))
DIR_FILE	=	$(addprefix Src/, $(FILE))
DIR_TESTS	=	$(addprefix Tests/, $(TEST))

OBJ_SRC		=	$(DIR_SRC:.cpp=.o)
OBJ_FILE	=	$(DIR_FILE:.cpp=.o)
OBJ			=	$(OBJ_SRC) $(OBJ_FILE)

NAME		=	pbrain-gomoku-ai

CPPFLAGS	=	-I./Include/ -I./Include/Interface -I./Include/Brain

WFLAGS		=	-W -Wall -Wextra -Werror

LCRITER		= $(shell pkg-config --libs --cflags criterion) --coverage

$(NAME): $(OBJ)
	g++ -o $@ $^ $(CPPFLAGS) $(WFLAGS)

debug: $(OBJ)
	g++ -o $(NAME) $^ $(CPPFLAGS) $(WFLAGS) -ggdb3

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -rf unit_tests/

re: fclean $(NAME)

unit_tests:	fclean
	mkdir -p unit_tests
	g++ -o unit_tests/unit_tests $(OBJ) $(DIR_FILE) $(DIR_TESTS) $(CPPFLAGS) \
	$(WFLAGS) $(LCRITER)

tests_run:	unit_tests
	./unit_tests/unit_tests

.PHONY: all clean fclean re unit_tests tests_run
