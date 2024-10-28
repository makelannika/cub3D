# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/10 19:33:06 by amakela           #+#    #+#              #
#    Updated: 2024/10/27 23:12:28 by amakela          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror

CFILES = src/ft_atoi.c			src/ft_bzero.c		src/ft_calloc.c		src/ft_isalnum.c	\
		 src/ft_isalpha.c		src/ft_isascii.c	src/ft_isdigit.c	src/ft_isprint.c	\
		 src/ft_itoa.c			src/ft_memchr.c		src/ft_memcmp.c		src/ft_memcpy.c		\
		 src/ft_memmove.c		src/ft_memset.c		src/ft_printchar.c	src/ft_printf.c		\
		 src/ft_printhex.c		src/ft_printnbr.c	src/ft_printstr.c	src/ft_putchar_fd.c	\
		 src/ft_putendl_fd.c	src/ft_putnbr_fd.c	src/ft_putstr_fd.c	src/ft_split.c		\
		 src/ft_strchr.c		src/ft_strdup.c		src/ft_striteri.c	src/ft_strjoin.c	\
		 src/ft_strlcat.c		src/ft_strlcpy.c	src/ft_strlen.c		src/ft_strmapi.c	\
		 src/ft_strncmp.c		src/ft_strnstr.c	src/ft_strrchr.c	src/ft_strtrim.c	\
		 src/ft_substr.c		src/ft_tolower.c	src/ft_toupper.c	src/ft_atol.c		\
		 src/get_next_line.c

BONUSES = src/ft_lstnew_bonus.c 	src/ft_lstadd_front_bonus.c		src/ft_lstsize_bonus.c		\
		  src/ft_lstlast_bonus.c	src/ft_lstadd_back_bonus.c		src/ft_lstdelone_bonus.c	\
		  src/ft_lstclear_bonus.c	src/ft_lstiter_bonus.c			src/ft_lstmap_bonus.c

INCLUDE	= -I /include

OFILES = $(CFILES:.c=.o)

BOFILES = $(BONUSES:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)
	
$(NAME): $(OFILES)
	@ar rcs $(NAME) $(OFILES)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)


bonus : .bonus

.bonus : $(BOFILES)
	ar rcs $(NAME) $(BOFILES)
	@touch .bonus

clean:
	@rm -f $(OFILES) $(BOFILES) .bonus

fclean: clean
	@rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
