# # Makefile for minishell

# Colour codes
RED = \033[01;31m
YELLOW = \033[01;33m
GREEN = \033[01;32m
RESET = \033[0m

# Executable name
NAME = minishell

# Source directories
SRC_DIR = ./src

# Libft
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

# Other directories
OBJ_DIR = ./obj
INCLUDE_DIR = ./include

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP -I$(INCLUDE_DIR) -I$(LIBFT_DIR)/include
LFLAGS = -L$(LIBFT_DIR) -lft -lreadline

# Remove command
RM = rm -rf

# Source files
SRC = init.c \
		main.c

# Object files
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
DEPS = $(OBJ:.o=.d)

# Include dependency files
-include $(DEPS)

# Compile individual source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Phony targets
all: $(NAME)

clean:
	@cd $(LIBFT_DIR) && $(MAKE) --quiet clean
	@$(RM) $(OBJ_DIR)
	@echo "$(RED)✔️ clean $(NAME)$(RESET)"

fclean: clean
	@cd $(LIBFT_DIR) && $(MAKE) --quiet fclean
	@$(RM) $(NAME)
	@echo "$(RED)✔️ fclean $(NAME)$(RESET)"

re: fclean all

# Target rules
$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LFLAGS)
	@echo "$(GREEN)✔️ $(NAME) created$(RESET)"

# Create object directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Library compilation
$(LIBFT): $(LIBFT_DIR)
	@echo "$(YELLOW)compiling...$(RESET)"
	@cd $(LIBFT_DIR) && $(MAKE) --quiet
	@echo "$(GREEN)✔️ libft created$(RESET)"

.PHONY: all clean fclean re
