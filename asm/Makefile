##
## EPITECH PROJECT, 2020
## LibErty
## File description:
## Makefile
##

SHELL 			=	bash

CC			=	gcc

IFLAGS 			=	-I../include

LDFLAGS  		=	-L../erty -lerty

DEBUG_FLAGS 		= 	-g3 -ggdb

TEST_FLAGS 		= 	--coverage -lcriterion

WFLAGS 			=	-W -Wall -Wextra -Werror -Wno-missing-field-initializers

POSIX_FLAGS 		=	-D_POSIX_C_SOURCE=200809L -D_GNU_SOURCE

CFLAGS 			?=	 $(WFLAGS) $(POSIX_FLAGS) $(IFLAGS) $(LDFLAGS)

DEBUG 			?=	0
GRAPH 			?=	0

ifeq ($(DEBUG),1)
	CFLAGS 		+=	$(DEBUG_FLAGS)
endif

MAIN			=	main.c

SRC			= 	./is_token.c \
				./label.c \
				./label_replace.c \
				./op.c \
				./open_file.c \
				./parse_argument.c \
				./parse_label_asm.c \
				./parse_line.c \
				./parse_opcode.c \
				./parse_register.c \
				./parse_value.c \
				./pre_parsing.c \
				./read_header.c \
				./util.c


OBJ 		= 	$(SRC:.c=.o) \
			$(MAIN:.c=.o)

NAME 		=	asm

all:
	@rm -f $(NAME)
	@make -j -C . $(NAME) --silent

$(NAME):
	@make -j -C . info --silent
	@make -j -C ../erty all --silent
	@make -j -C . build --silent

%.o: %.c
	@$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@
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
	@printf "[Info] Linking objects with:"
	@printf "\n\tCC        = $(CC)"
	@printf "\n\tCFLAGS    = $(CFLAGS)"
	@printf "\n\tAR        = $(AR)"
	@printf "\n\tSHELL     = $(SHELL)\n"

.PHONY:		all build_lib copy clean fclean re
