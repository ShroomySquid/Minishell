# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/30 09:59:24 by fbarrett          #+#    #+#              #
#    Updated: 2023/12/18 11:05:35 by fbarrett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

MY_LIBRARY	=	./Libft/

O_DIRECT	=	./bin/

MY_BONUS	=	./bonus/

MY_SOURCES	=	print_line.c

MY_OBJECTS	=	$(addprefix $(O_DIRECT), $(MY_SOURCES:%.c=%.o))

CC	=	gcc

LIBFLAGS = -L./Libft/ -lft -I.

CCFLAGS	=	-Wall -Wextra -Werror

all:	$(NAME)

$(NAME): $(O_DIRECT) $(MY_OBJECTS) $(MY_LIBRARY)
	@make -C $(MY_LIBRARY)
	$(CC) $(CCFLAGS) -o $(NAME) $(MY_OBJECTS) $(LIBFLAGS)

bonus: $(O_DIRECT) $(MY_BONUS) $(MY_LIBRARY) 
	@make -C $(MY_LIBRARY)
	@make -C $(MY_BONUS)

$(O_DIRECT)%.o: %.c
	$(CC) $(CCFLAGS) -o $@ -c $< 

$(O_DIRECT):	
	mkdir -p -m 777 $(O_DIRECT)

clean:
	rm -f $(O_DIRECT)*.o
	rm -f *.o
	rm -rf *.dSYM

fclean:	clean
	rm -f $(NAME)
	rm -rf $(O_DIRECT)

re:	fclean $(NAME)

.PHONY:	all clean fclean re test bonus bin pipex_bonus
