##
## EPITECH PROJECT, 2020
## LibErty
## File description:
## Makefile
##

SHELL 			=	bash

CC				=	gcc

IFLAGS 			=	-I../include

LFLAGS  		=	-L../erty -lerty

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

SRC 		= 	./src/vm_init.c \
				./src/champion_loader.c

OBJ 		=	$(MAIN:.c=.o) \
				$(SRC:.c=.o)

NAME 		=	corewar

all:
	@rm -f $(NAME)
	@make -j -C . $(NAME) --silent

$(NAME):
	@make -j -C . info --silent
	@make -j -C ../erty all --silent
	@make -j -C . build --silent

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "[Linked] % 43s\n" $@ | tr ' ' '.'

build: $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)
	@printf "[Linked] % 43s\n" $(NAME) | tr ' ' '.'
	@printf "[Linked all vm files]\n"

clean:
	@make -j -C ../erty clean --silent
	@rm -f $(OBJ) $(NAME)
	@printf "Finished removing objects\n"
	@find . -type f \( -name "\#*\#" -o -name "*.swp" \) -delete

fclean:		clean
	@make -j -C ../erty fclean --silent
	@find . -type f \( -name "*~" -o -name "*.a" -o -name "vgcore.*" \) -delete

re:
	@make -j -C . fclean --silent
	@make -j -C . all --silent

info:
	@printf  "██████╗ ██████╗  ██████╗ ███████╗██╗    ██╗ █████╗ ██████╗  ██╗   ██╗███╗   ███╗\n"
	@printf  "██╔════╝██╔═══██╗██╔══██╗██╔════╝██║    ██║██╔══██╗██╔══██╗ ██║   ██║████╗ ████║\n"
	@printf  "██║     ██║   ██║██████╔╝█████╗  ██║ █╗ ██║███████║██████╔╝ ██║   ██║██╔████╔██║\n"
	@printf  "██║     ██║   ██║██╔══██╗██╔══╝  ██║███╗██║██╔══██║██╔══██╗ ╚██╗ ██╔╝██║╚██╔╝██║\n"
	@printf  "██████╗╚██████╔╝ ██║  ██║███████╗╚███╔███╔╝██║  ██║██║  ██║  ╚████╔╝ ██║ ╚═╝ ██║\n"
	@printf  "╚═════╝ ╚═════╝  ╚═╝  ╚═╝╚══════╝ ╚══╝╚══╝ ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═══╝  ╚═╝     ╚═╝\n"
	@printf "[Info] Linking objects with:"
	@printf "\n\tCC        = $(CC)"
	@printf "\n\tCFLAGS    = $(CFLAGS)"
	@printf "\n\tAR        = $(AR)"
	@printf "\n\tSHELL     = $(SHELL)\n"

.PHONY:		all build_lib copy clean fclean re
