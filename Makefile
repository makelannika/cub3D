# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/24 13:25:09 by amakela           #+#    #+#              #
#    Updated: 2024/09/05 16:39:40 by amakela          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3d

LIBFTDIR	= libft
LIBFT		= $(LIBFTDIR)/libft.a

MLXDIR		= MLX42
MLX42		= $(MLXDIR)/build/libmlx42.a

HEADERS 	= -I /include -I $(MLX42)/include

LIBS		= $(LIBFT) $(MLX42) -lglfw -L"~/.brew/Cellar/glfw/3.4/lib/"

CFLAGS		= -Wall -Wextra -Werror -g

CC			= cc

CFILES		=	src/game.c				src/main.c				src/parse_elements.c	\
				src/parse_map.c			src/utils_cleaning.c	src/utils_parsing.c		\

OFILES		= $(CFILES:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)
	
all: $(MLX42) $(NAME)

$(MLX42):
	@cmake $(MLXDIR) -B $(MLXDIR)/build && make -C $(MLXDIR)/build -j4

$(NAME): $(OFILES)
	make -C $(LIBFTDIR)
	$(CC) $(OFILES) $(LIBS) -o $(NAME)

clean:
	rm -f $(OFILES)
	make -C $(LIBFTDIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFTDIR) fclean
	rm -rf $(MLX42)/build

re: fclean all

.PHONY: all clean fclean re libmlx
