# Makefile for libft

# Library name
NAME = libft.a
NAME_BONUS = libft_bonus.a
NAME_FULL = libft_full.a

# Source directories
SRC_DIR = ./src
SRC_BONUS_DIR = $(SRC_DIR)/bonus
SRC_GNL_DIR = $(SRC_DIR)/get_next_line
SRC_PRINTF_DIR = $(SRC_DIR)/ft_printf
SRC_PRINTF_FD_DIR = $(SRC_DIR)/ft_printf_fd

# Headers
HEADERS_DIR = ./include
HEADERS = $(HEADERS_DIR)/libft.h

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(HEADERS_DIR)

# Archiver
AR = ar rcs

# Remove command
RM = rm -f

# Source files
SRC = ft_atoi.c \
      ft_bzero.c \
      ft_calloc.c \
      ft_free_str_arr.c \
      ft_isalnum.c \
      ft_isalpha.c \
      ft_isascii.c \
      ft_isdigit.c \
      ft_isprint.c \
      ft_itoa.c \
      ft_memchr.c \
      ft_memcmp.c \
      ft_memcpy.c \
      ft_memmove.c \
      ft_memset.c \
      ft_putchar_fd.c \
      ft_putendl_fd.c \
      ft_putnbr_fd.c \
      ft_putstr_fd.c \
      ft_split.c \
      ft_strchr.c \
      ft_strcmp.c \
      ft_strdup.c \
      ft_striteri.c \
      ft_strjoin.c \
      ft_strlcat.c \
      ft_strlcpy.c \
      ft_strlen.c \
      ft_strmapi.c \
      ft_strncmp.c \
      ft_strnstr.c \
      ft_strrchr.c \
      ft_strtrim.c \
      ft_substr.c \
      ft_tolower.c \
      ft_toupper.c

SRC_BONUS = ft_lstadd_back.c \
            ft_lstadd_front.c \
            ft_lstclear.c \
            ft_lstdelone.c \
            ft_lstiter.c \
            ft_lstlast.c \
            ft_lstmap.c \
            ft_lstnew.c \
            ft_lstsize.c

SRC_GNL = get_next_line.c

SRC_PRINTF = ft_printf_utils.c \
             ft_printf_utils2.c \
             ft_printf.c

SRC_PRINTF_FD = ft_printf_fd_utils.c \
                ft_printf_fd_utils2.c \
                ft_printf_fd.c

# Object files
OBJ = $(SRC:%.c=$(SRC_DIR)/%.o)
OBJ_BONUS = $(SRC_BONUS:%.c=$(SRC_BONUS_DIR)/%.o)
OBJ_GNL = $(SRC_GNL:%.c=$(SRC_GNL_DIR)/%.o)
OBJ_PRINTF = $(SRC_PRINTF:%.c=$(SRC_PRINTF_DIR)/%.o)
OBJ_PRINTF_FD = $(SRC_PRINTF_FD:%.c=$(SRC_PRINTF_FD_DIR)/%.o)
OBJ_FULL = $(OBJ) $(OBJ_BONUS) $(OBJ_GNL) $(OBJ_PRINTF) $(OBJ_PRINTF_FD)

# Compile individual source files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

# Phony Targets
all: $(NAME)

clean:
	@$(RM) $(OBJ_FULL)

fclean: clean
	@$(RM) $(NAME) $(NAME_BONUS) $(NAME_FULL)

re: fclean all

bonus: $(NAME_BONUS)

# (bonus, get_next_line, ft_printf, ft_printf_fd)
full: $(NAME_FULL)

# Target Rules
$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)

$(NAME_BONUS): $(OBJ_BONUS)
	@$(AR) $(NAME_BONUS) $(OBJ_BONUS)

$(NAME_FULL): $(OBJ_FULL)
	@$(AR) $(NAME_FULL) $(OBJ_FULL)

.PHONY: all clean fclean re bonus full
