# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/06 21:19:50 by kiroussa          #+#    #+#              #
#    Updated: 2024/09/19 17:29:51 by babonnet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#
# Vars
#

NAME			=	libhtab.a

BUILD_DIR		=	build

SRC				=	htab.c		\
					hentry.c	\
					pchunk.c	\
					hutils.c

SRC_DIR			=	src

SRC				:=	$(addprefix $(SRC_DIR)/, $(SRC))

OBJ_DIR			=	$(BUILD_DIR)/obj

OBJ				=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

INCLUDE_DIR		= 	include

CC				=	gcc

CFLAGS			= 	-Wall -Wextra -Werror -g -mavx2 -O3 -flax-vector-conversions

COPTS			= 	-I ./$(INCLUDE_DIR)

FILE			=	$(shell ls -lR $(SRC_DIR) | grep -F .c | wc -l)
CMP				=	1

RM				=	rm -rf

#
# Rules
#

all:		$(NAME)

$(NAME):	$(OBJ)
	@ar -rcs $@ $^
	@printf "$(BOLD)   > $(GREEN)$@ built !\n$(RESET)"

$(OBJ_DIR)/%.o:	%.c
	@mkdir -p $(@D)
	@echo "$(BOLD)  🔩 building $(RESET)$(ITALIC)$@$(RESET)$(BOLD) from $(RESET)$(ITALIC)$^ ...$(RESET)"
	@$(CC) $(CFLAGS) $(COPTS) -c $< -o $@

test:			all
	$(CC) $(CFLAGS) $(COPTS) main.c $(NAME) -o htab_test
	@printf "$(BOLD)   > $(GREEN)htab_test built !\n$(RESET)"

remake:			all

clean:			
	$(RM) $(BUILD_DIR)

fclean:			clean
	$(RM) $(NAME)
	$(RM) htab_test

re:				fclean all

.PHONY:			all clean fclean remake re test
.SILENT:		all clean fclean remake re test

#
# Colors
#

BLACK		=	\033[30m
RED			=	\033[31m
GREEN		=	\033[32m
YELLOW		=	\033[33m
BLUE		=	\033[34m
MAGENTA		=	\033[35m
CYAN		=	\033[36m
WHITE		=	\033[37m

BOLD		=	\033[1m
ITALIC		=	\033[3m

RESET		=	\033[0m
LINE_CLR	=	\33[2K\r
