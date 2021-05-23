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

NCURSES_FLAGS 		= 	-lncurses

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

SRC			= 	./src/vm_init.c \
				./src/op.c \
				./src/opts.c \
				./src/opts2.c \
				./src/corewar_loader.c \
				./src/champion/champion_loader.c \
				./src/champion/champion_open.c \
				./src/champion/write_champion_in_ram.c \
				./src/instruction/add_sub.c \
				./src/instruction/live.c \
				./src/instruction/aff.c \
				./src/instruction/bitwise.c \
				./src/instruction/check.c \
				./src/instruction/check2.c \
				./src/instruction/has_coding_byte.c \
				./src/instruction/fail.c \
				./src/instruction/fork.c \
				./src/instruction/ld.c \
				./src/instruction/st.c \
				./src/instruction/zjmp.c \
				./src/proc/proc.c \
				./src/proc/tick_cycle_proc.c \
				./src/util/arg.c \
				./src/util/index_memory.c \
				./src/util/memory_reader.c \

GRAPH_SRC 	= 	$(SRC) \
			../bonus/src/main.c \
			../bonus/src/color.c \
			../bonus/src/draw.c

OBJ			?=

ifeq ($(GRAPH),1)
	CFLAGS 		+= 	$(NCURSES_FLAGS) -lcsfml-audio
	CFLAGS 		+= 	-DGRAPHIC
	OBJ 		+= 	$(GRAPH_SRC:.c=.o)
	CFLAGS 		+= 	-I ./src/graphical/include
else
	OBJ 		+= 	$(SRC:.c=.o)
	OBJ 		+= 	$(MAIN:.c=.o)
endif

NAME 		=	corewar

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
