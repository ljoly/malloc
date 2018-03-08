# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/04 11:00:36 by ljoly             #+#    #+#              #
#    Updated: 2018/03/07 23:04:59 by ljoly            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LINK_NAME = libft_malloc.so


SRC = malloc.c init.c map_zone.c allocate_meta.c free.c realloc.c \
	show_alloc_memory.c show_alloc_utils.c

SRC_PATH = ./src/
OBJ_PATH = ./obj/

OBJ = $(addprefix $(OBJ_PATH), $(SRC:.c=.o))

FLAGS = -Wall -Werror -Wextra
LIBFT = ./libft/
HEADER_LIB = ./libft/includes/
HEADER = ./includes

RED=\033[1;31m
GREEN=\033[1;32m
NC=\033[0m

.SILENT:

all: $(NAME)

$(NAME): obj $(OBJ)
	gcc $(FLAGS) -shared -o $(NAME) -I $(HEADER_LIB) -I $(HEADER) $(OBJ) -L $(LIBFT) -lft
	@ln -sf $(NAME) $(LINK_NAME)
	@printf "\n$(GREEN)[✓]$(NC)\x1B[32mShared object $(NAME) ready !\x1B[37m\n"

obj:
	# @make -C $(LIBFT)
	# @printf "\n\x1B[38;5;208mCompiling $(NAME)...\n\x1b[37m"
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	gcc $(FLAGS) -I $(LIBFT) -I $(HEADER_LIB) -I $(HEADER) -o $@ -c $<
	@printf "\e[38;5;208m▒\e[0m"

clean:
	# @make -C $(LIBFT) clean
	@rm -rf $(OBJ_PATH)
	@printf "$(RED)[-]$(NC)Obj files deleted\n"

fclean: clean
	# @make -C $(LIBFT) fclean
	@rm -f $(NAME)
	@rm -f $(LINK_NAME)
	@rm -f a.out
	@printf "$(RED)[-]$(NC)Shared object $(NAME) deleted\n"

re: fclean all

.PHONY: all clean fclean re
