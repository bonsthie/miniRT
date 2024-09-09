NAME = miniRT
NAME_BONUS = miniRT_bonus

##################################### DATA ##########################################
CC := gcc
CFLAGS = -Wall -Wextra -Werror -mavx2 -MMD -MP -g -fopenmp
SRC_DIR := src
SRC_DIR_BONUS := src_bonus
OBJ_DIR := obj
OBJ_DIR_BONUS := obj_bonus
HSRCS := include
HSRCS_BONUS := include_bonus

#source file are declared in the sources.mk file
include sources.mk

OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_BONUS := $(SRC_BONUS:$(SRC_DIR_BONUS)/%.c=$(OBJ_DIR_BONUS)/%.o)

################################### LIBRARIES #######################################
LIBRARIES = 

LIBRARIES += LIBFT
LIBFT_DIR = lib/libft
LIBFT_BINARY = $(LIBFT_DIR)/libft.a
LIBFT_FLAG = -lft
LIBFT_INCLUDE = .

LIBRARIES += LIBMLX
LIBMLX_DIR = lib/MacroLibX
LIBMLX_BINARY = $(LIBMLX_DIR)/libmlx.so
LIBMLX_FLAG = -lmlx -lSDL2 -Wl,-rpath,$(LIBMLX_DIR)
LIBMLX_INCLUDE = includes

LIBRARIES += LIBHTABLE
LIBHTABLE_DIR = lib/htable
LIBHTABLE_BINARY = $(LIBHTABLE_DIR)/libhtab.a
LIBHTABLE_FLAG = -lhtab
LIBHTABLE_INCLUDE = include

#include lib for exec
LIB = $(foreach lib,$(LIBRARIES),-L$($(lib)_DIR) $($(lib)_FLAG))
#include lib for *.o
LIB_DIR = $(foreach lib,$(LIBRARIES),-I $($(lib)_DIR)/$($(lib)_INCLUDE))
#build all lib
LIBS_BINARYS += $(foreach lib,$(LIBRARIES), $($(lib)_BINARY))

# Additional linker flags
ADDITIONAL_FLAGS = -lm -lrt

################################ MAKEFILE RULES #####################################

all: $(NAME)

$(NAME): $(LIBS_BINARYS) $(OBJ)
	@echo "$(GREEN)Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJ) -o $@ $(LIB) $(ADDITIONAL_FLAGS)

$(NAME_BONUS): $(LIBS_BINARYS) $(OBJ_BONUS)
	@echo "$(GREEN)Linking bonus...$(NC)"
	@$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME)_bonus $(LIB) $(ADDITIONAL_FLAGS) $(LIBS_BINARYS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "[$(YELLOW)$(CC)$(NC)] Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) -I$(HSRCS) $(LIB_DIR) -c $< -o $@

$(OBJ_DIR_BONUS)/%.o: $(SRC_DIR_BONUS)/%.c
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling $(notdir $<)...$(NC)"
	@$(CC) $(CFLAGS) -I$(HSRCS_BONUS) $(LIB_DIR) -c $< -o $@

$(LIBS_BINARYS):
	@echo "$(PURPLE)Building library $(notdir $@)...$(NC)"
	@$(MAKE) -C $(@D) -j$(nproc) --no-print-directory all

clean:
	@if [ -d $(OBJ_DIR) ]; then \
		echo "$(RED)Cleaning object files $(NAME)...$(NC)"; \
		rm -rf $(OBJ_DIR); \
		fi
	@if [ -d $(OBJ_DIR_BONUS) ]; then \
		echo "$(RED)Cleaning object files $(NAME_BONUS)...$(NC)"; \
		rm -rf $(OBJ_DIR_BONUS); \
		fi

bonus : $(NAME_BONUS)

lclean:
	@echo "$(RED)Cleaning libraries obj...$(NC)"
	@$(foreach lib,$(LIBRARIES),$(MAKE) -C $($(lib)_DIR) clean > /dev/null;)

fclean: clean
	@echo "$(RED)Cleaning executable $(NAME)...$(NC)"
	@if [ -f $(NAME) ]; then \
		echo "$(RED)Cleaning executable $(NAME)...$(NC)"; \
		rm -f $(NAME); \
		fi
	@if [ -f $(NAME_BONUS) ]; then \
		echo "$(RED)Cleaning executable $(NAME_BONUS)...$(NC)"; \
		rm -f $(NAME_BONUS); \
		fi
	@echo "$(RED)Cleaning libraries...$(NC)"
	@$(foreach lib,$(LIBRARIES),$(MAKE) -C $($(lib)_DIR) fclean > /dev/null ;)

debug: CFLAGS += -g 
debug: clean $(NAME)

re: fclean all

-include $(OBJ:.o=.d)

.PHONY: all clean fclean lclean re help

##################################### COLORS ########################################

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[1;33m
PURPLE = \033[0;35m
NC = \033[0m
