# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/30 09:59:24 by fbarrett          #+#    #+#              #
#    Updated: 2023/12/09 11:04:20 by fbarrett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

MY_SOURCES	=	ft_isdigit.c ft_putendl_fd.c ft_strlen.c ft_isprint.c \
	ft_putstr_fd.c ft_strmapi.c ft_itoa.c ft_split.c ft_strncmp.c ft_atoi.c ft_memchr.c\
	ft_strchr.c ft_strnstr.c ft_bzero.c ft_memcmp.c ft_strdup.c ft_strrchr.c\
	ft_putnbr_fd.c ft_calloc.c ft_memcpy.c ft_striteri.c ft_strtrim.c ft_isalnum.c\
	ft_memmove.c ft_isalpha.c ft_memset.c ft_strjoin.c	\
	ft_substr.c ft_isascii.c ft_putchar_fd.c ft_strlcat.c ft_tolower.c ft_toupper.c \
	ft_strlcpy.c ft_putnbrbase_fd.c base_type_check.c array_int_func.c	get_next_line.c

BONUS_SOURCES	=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

FT_PRINTF_SOURCES	=	additions/ft_printf/ft_parse.c additions/ft_printf/ft_printf.c additions/ft_printf/ft_put001.c additions/ft_printf/ft_put002.c

MY_OBJECTS	=	$(MY_SOURCES:%.c=%.o)

MY_BONUS	=	$(BONUS_SOURCES:%.c=%.o)

MY_FT_PRINTF	=	$(FT_PRINTF_SOURCES:%.c=%.o)

CC	=	gcc

LIBFLAGS = -L. -lft -I. -I./additions/ft_printf

CCFLAGS	=	-Wall -Wextra -Werror

all:	$(NAME)

$(NAME): $(MY_OBJECTS) $(MY_BONUS) $(MY_FT_PRINTF)
	ar rcs libft.a $(MY_OBJECTS) $(MY_BONUS) $(MY_FT_PRINTF)

test:	$(NAME) libft.h
	$(CC) $(CCFLAGS) $(LIBFLAGS) main.c -o test

%.o:%.c libft.h
	$(CC) $(CCFLAGS) -c $< -o $@ $(LIBFLAGS)

clean:
	rm -f $(MY_OBJECTS) $(MY_BONUS) $(MY_FT_PRINTF)

fclean:	clean
	rm -f $(NAME) test a.out

re:	fclean $(NAME)

.PHONY:	clean all fclean re test
