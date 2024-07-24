# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/10 19:33:06 by amakela           #+#    #+#              #
#    Updated: 2024/07/24 17:49:09 by amakela          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror

CFILES = ft_atoi.c			ft_bzero.c		ft_calloc.c		ft_isalnum.c	\
		 ft_isalpha.c		ft_isascii.c	ft_isdigit.c	ft_isprint.c	\
		 ft_itoa.c			ft_memchr.c		ft_memcmp.c		ft_memcpy.c		\
		 ft_memmove.c		ft_memset.c		ft_printchar.c	ft_printf.c		\
		 ft_printhex.c		ft_printnbr.c	ft_printstr.c	ft_putchar_fd.c	\
		 ft_putendl_fd.c	ft_putnbr_fd.c	ft_putstr_fd.c	ft_split.c		\
		 ft_strchr.c		ft_strdup.c		ft_striteri.c	ft_strjoin.c	\
		 ft_strlcat.c		ft_strlcpy.c	ft_strlen.c		ft_strmapi.c	\
		 ft_strncmp.c		ft_strnstr.c	ft_strrchr.c	ft_strtrim.c	\
		 ft_substr.c		ft_tolower.c	ft_toupper.c					\
		 get_next_line.c	ft_atol.c

BONUSES = ft_lstnew_bonus.c 	ft_lstadd_front_bonus.c		ft_lstsize_bonus.c		\
		  ft_lstlast_bonus.c	ft_lstadd_back_bonus.c		ft_lstdelone_bonus.c	\
		  ft_lstclear_bonus.c	ft_lstiter_bonus.c			ft_lstmap_bonus.c

OFILES = $(CFILES:.c=.o)

BOFILES = $(BONUSES:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)
	
$(NAME): $(OFILES)
	@ar rcs $(NAME) $(OFILES)

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
