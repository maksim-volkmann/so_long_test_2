# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 16:31:03 by mvolkman          #+#    #+#              #
#    Updated: 2024/03/21 12:37:48 by mvolkman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Source files for so_long
SRC = \
	so_long.c \
	read_map.c \
	validate_map.c \
	check_map_path.c \
	initialize.c \


# Object files
OBJ = $(SRC:.c=.o)

# Library directories and flags for libft
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

# Library directories and flags for libmlx42
LIBMLX42_DIR = ./MLX42
LIBMLX42 = $(LIBMLX42_DIR)/build/libmlx42.a

# Include directories for libft and libmlx42
INCLUDES = -I$(LIBFT_DIR)/include \
           -I$(LIBMLX42_DIR)/include \
           -I./include

# Output executable name
NAME = so_long

# Colors used for terminal output.
GREEN = \033[0;32m
BLUE = \033[0;34m
ORANGE = \033[38;5;214m
RED = \033[0;31m
YELLOW = \033[0;33m
WHITE = \033[0;37m

# Rules
all: $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(WHITE)"

$(NAME): $(OBJ) $(LIBFT) $(LIBMLX42)
	@echo "$(BLUE)Building $(NAME)$(WHITE)"
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(LIBMLX42) -Iinclude -lglfw
	@echo "$(GREEN)$(NAME) created successfully!$(WHITE)"

$(LIBFT):
	@echo "$(BLUE)Building $(LIBFT)$(WHITE)"
	make -C $(LIBFT_DIR)

$(LIBMLX42):
	@echo "$(BLUE)Building $(LIBMLX42)$(WHITE)"
	cd $(LIBMLX42_DIR) && cmake -B build && cmake --build build -j4

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	@echo "$(GREEN)Compiled $< successfully!$(WHITE)"

clean:
	@echo "$(RED)Cleaning object files...$(WHITE)"
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(RED)Cleaning binaries...$(WHITE)"
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

# CC = CC

# CFLAGS = -Wall -Wextra -Werror

# SRC = \
# 	dependencies/libft/ft_isalpha.c \
# 	dependencies/libft/ft_isdigit.c \
# 	dependencies/libft/ft_isalnum.c \
# 	dependencies/libft/ft_isascii.c \
# 	dependencies/libft/ft_isprint.c \
# 	dependencies/libft/ft_strlen.c \
# 	dependencies/libft/ft_toupper.c \
# 	dependencies/libft/ft_tolower.c \
# 	dependencies/libft/ft_memset.c \
# 	dependencies/libft/ft_bzero.c \
# 	dependencies/libft/ft_memcpy.c \
# 	dependencies/libft/ft_memmove.c \
# 	dependencies/libft/ft_strlcpy.c \
# 	dependencies/libft/ft_strlcat.c \
# 	dependencies/libft/ft_strchr.c \
# 	dependencies/libft/ft_strrchr.c \
# 	dependencies/libft/ft_memchr.c \
# 	dependencies/libft/ft_strncmp.c \
# 	dependencies/libft/ft_memcmp.c \
# 	dependencies/libft/ft_strnstr.c \
# 	dependencies/libft/ft_atoi.c \
# 	dependencies/libft/ft_calloc.c \
# 	dependencies/libft/ft_strdup.c \
# 	dependencies/libft/ft_substr.c \
# 	dependencies/libft/ft_strjoin.c \
# 	dependencies/libft/ft_strtrim.c \
# 	dependencies/libft/ft_itoa.c \
# 	dependencies/libft/ft_strmapi.c \
# 	dependencies/libft/ft_striteri.c \
# 	dependencies/libft/ft_putchar_fd.c \
# 	dependencies/libft/ft_putstr_fd.c \
# 	dependencies/libft/ft_putendl_fd.c \
# 	dependencies/libft/ft_putnbr_fd.c \
# 	dependencies/libft/ft_split.c

# OBJ = $(SRC:.c=.o)

# NAME = so_long.a

# all: $(NAME)

# $(NAME): $(OBJ)
# 	ar rcs $(NAME) $(OBJ)

# bonus: $(BONUS_OBJ)
# 	ar rcs $(NAME) $(BONUS_OBJ)

# clean:
# 	rm -f $(OBJ) $(BONUS_OBJ)

# fclean: clean
# 	rm -f $(NAME)

# re: fclean all

# .PHONY: all clean fclean re
