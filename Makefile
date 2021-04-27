##
## EPITECH PROJECT, 2020
## LibErty
## File description:
## Makefile
##

GREEN 			=	\x1b[32;01m
RED 			=	\x1b[31;01m
YELLOW 			=	\x1b[33;01m
WHITE 			=	\x1b[00;00m
CYAN 			=	\x1b[34;01m
DEFAULT 		= 	\x1b[36;01m

SHELL 			=	bash

CC				=	gcc

IFLAGS 			=	-I./include

LFLAGS  		=	-L./erty -lerty

DEBUG_FLAGS 	= 	-g3 -ggdb

TEST_FLAGS 		= 	--coverage -lcriterion

WFLAGS 			=	-W -Wall -Wextra -Werror

POSIX_FLAGS 	=	-D_POSIX_C_SOURCE=200809L -D_GNU_SOURCE

STANDARD_FLAGS 	=	-std=c99

CFLAGS 			?=	 $(WFLAGS) $(POSIX_FLAGS) $(STANDARD_FLAGS) $(IFLAGS) $(LFLAGS)

DEBUG 			?=	0

ifeq ($(DEBUG),1)
	CFLAGS 		+=	$(DEBUG_FLAGS)
endif

MAIN 		=	main.c

SRC 		=

OBJ 		=	$(MAIN:.c=.o) \
				$(SRC:.c=.o)

NAME 		=	mysh

all:		$(NAME)	## Put whatever you want here (default : Call build_lib)

$(NAME): info
	@make -j -C ./erty all --silent
	@make -j -C . build --silent

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(GREEN)[$(YELLOW)Linked$(GREEN)]$(WHITE) % 43s\n$(DEFAULT)" $@ | tr ' ' '.'

build: $(OBJ) ## Build Mysh
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)
	@printf "$(GREEN)[$(YELLOW)Linked$(GREEN)]$(WHITE) % 43s$(DEFAULT)\n" $(NAME) | tr ' ' '.'
	@printf "$(GREEN)[$(CYAN)Linked all mysh files$(GREEN)]\n$(WHITE)"

clean:
	@make -j -C ./erty clean --silent
	@rm -f $(OBJ) $(NAME)
	@printf "\e[1;32mFinished removing objects\e[0m\n"
	@find . -type f \( -name "\#*\#" -o -name "*.swp" \) -delete

fclean:		clean
	@make -j -C ./erty fclean --silent
	@find . -type f \( -name "*~" -o -name "*.a" -o -name "vgcore.*" \) -delete

valgrind: build_lib main ## Build the lib the main.c and launch with valgrind
	valgrind --exit-on-first-error=yes ./erty

re:
	make -j -C . fclean --silent
	make -j -C . all --silent

info:
	@printf "$(GREEN)[$(YELLOW)Info$(GREEN)] $(WHITE)Linking objects with:"
	@printf "\n\t$(CYAN)CC        $(WHITE)= $(GREEN)$(CC)"
	@printf "\n\t$(CYAN)CFLAGS    $(WHITE)= $(GREEN)$(CFLAGS)$(DEFAULT)"
	@printf "\n\t$(CYAN)AR        $(WHITE)= $(GREEN)$(AR)$(DEFAULT)"
	@printf "\n\t$(CYAN)SHELL     $(WHITE)= $(GREEN)$(SHELL)$(DEFAULT)\n"

.PHONY:		all build_lib copy clean fclean re
