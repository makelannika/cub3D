# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/24 13:25:09 by amakela           #+#    #+#              #
#    Updated: 2024/10/29 18:40:00 by amakela          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

LIBFTDIR	= libft
LIBFT		= $(LIBFTDIR)/libft.a

MLXDIR		= MLX42
MLX42		= $(MLXDIR)/build/libmlx42.a

HEADERS 	= -I $(MLXDIR)/include -I $(LIBFTDIR)

LIBS		= $(LIBFT) $(MLX42) -lglfw -lm -L"~/.brew/Cellar/glfw/3.4/lib/"

CFLAGS		= -Wall -Wextra -Werror -g 

CC			= cc

CFILES		=	src/game.c				src/main.c				src/parse_file.c		\
				src/parse_map.c			src/movement.c			src/rotation.c			\
				src/utils_colors.c		src/drawing.c			src/ray_casting.c 		\
				src/utils_parsing.c		src/utils_ray_casting.c	src/utils_cleaning.c

OFILES		= $(CFILES:.c=.o)

all: $(MLX42) $(NAME)

$(NAME): $(OFILES)
	make -C $(LIBFTDIR)
	$(CC) $(OFILES) $(LIBS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(MLX42):
	@cmake $(MLXDIR) -B $(MLXDIR)/build && make -C $(MLXDIR)/build -j4

clean:
	rm -f $(OFILES)
	make -C $(LIBFTDIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFTDIR) fclean
	rm -rf $(MLXDIR)/build

re: fclean all

.PHONY: all clean fclean re libmlx
