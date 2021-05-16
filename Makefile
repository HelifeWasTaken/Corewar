##
## EPITECH PROJECT, 2020
## LibErty
## File description:
## Makefile
##

SHELL 			=	bash

CC				=	gcc

IFLAGS 			=	-I./include

LFLAGS  		=	-L./erty -lerty -lsdl

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

all: build		## Put whatever you want here (default : Call build_lib)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "[Linked] % 43s\n" $@ | tr ' ' '.'

build:
	@make -j -C ./vm/ all --silent

clean:
	@make -j -C ./vm/ clean  --silent
	@find . -type f \( -name "\#*\#" -o -name "*.swp" \) -delete

fclean:		clean
	@make -j -C ./vm fclean --silent
	@find . -type f \( -name "*~" -o -name "*.a" -o -name "vgcore.*" \) -delete

re:
	@make -j -C . fclean --silent
	@make -j -C . all --silent

.PHONY:		all build_lib copy clean fclean re
