# Makefile for minishell

# Colour codes
RED					=	\033[01;31m
YELLOW				=	\033[01;33m
GREEN				=	\033[01;32m
RESET				=	\033[0m

# Executable name
NAME				=	minishell

# Source directories
SRC_DIR				=	src

# Libft
LIBFT_DIR			=	libft
LIBFT				=	$(LIBFT_DIR)/libft.a

# Other directories
OBJ_DIR				=	obj
INCLUDE_DIR			=	include
CHECK_INPUT_DIR		=	check_input
PARSE_EXECUTE_DIR	=	parse_execute
BUILTINS_DIR		=	builtins
HEADERS				=	$(INCLUDE_DIR)/minishell.h \
						$(LIBFT_DIR)/include/libft.h

# Compiler and flags
CC = cc
CFLAGS				=	-Wall -Wextra -Werror -I$(INCLUDE_DIR) -I$(LIBFT_DIR)/include
LFLAGS				=	-L$(LIBFT_DIR) -lft -lreadline

# Remove command
RM					=	rm -rf

# Source files
SRC_CHECK_INPUT		=	check_line.c \
						env_variables.c \
						exit_status.c \
						quotes.c \
						redirections_space.c

SRC_PARSE_EXECUTE	=	cmd_data.c \
						cmd_in_out.c \
						cmd_input.c \
						cmd_output.c \
						execute.c \
						handle_commands.c \
						init_2.c \
						parse_execute.c \
						pid.c

SRC_BUILTINS		=	builtin_utils_2.c \
						builtin_utils.c \
						cd.c \
						echo.c \
						env.c \
						exit.c \
						export.c \
						pwd.c \
						unset.c

SRC 				=	$(addprefix $(CHECK_INPUT_DIR)/, $(SRC_CHECK_INPUT)) \
						$(addprefix $(PARSE_EXECUTE_DIR)/, $(SRC_PARSE_EXECUTE)) \
						$(addprefix $(BUILTINS_DIR)/, $(SRC_BUILTINS)) \
						clean_up_2.c \
						clean_up.c \
						err_msg.c \
						init.c \
						main.c \
						signals.c

# Object files
OBJ					=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Compile individual source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
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

# Create directories for object files
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/$(CHECK_INPUT_DIR)
	@mkdir -p $(OBJ_DIR)/$(PARSE_EXECUTE_DIR)
	@mkdir -p $(OBJ_DIR)/$(BUILTINS_DIR)

# Library compilation
$(LIBFT): $(LIBFT_DIR)
	@echo "$(YELLOW)compiling...$(RESET)"
	@cd $(LIBFT_DIR) && $(MAKE) --quiet
	@echo "$(GREEN)✔️ libft created$(RESET)"

.PHONY: all clean fclean re
