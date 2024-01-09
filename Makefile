CFLAGS= -g -Wextra -Wall -Werror
LIBS	:= -lft -L./lib/libft
NAME = minishell
OBJECTS = src/main.o src/ft_split_quote.o src/minishell_utils.o
DEPS = -I./include -I./lib/libft
INCLUDES = include/minishell.h


all: space
	@echo "\033[1;32mMaking libft:\033[0m"
	@$(MAKE) -C ./lib/libft 2>&1 | (grep -v "make\[1\]" || echo "\033[1;33mNothing to be done for libft\033[0m\n")
	@echo "\033[1;32mMaking $(NAME):\033[0m"
	@$(MAKE) $(NAME) 2>&1 | (grep -v "make\[1\]" || echo "\033[1;33mNothing to be done for $(NAME)\033[0m\n")

$(NAME): $(OBJECTS) $(INCLUDES)
	@echo
	$(CC) $(OBJECTS) $(LIBS) -o $(NAME) $(CFLAGS) $(DEPS)
	@echo "\033[1;32m$(NAME) compiled\033[0m"
	@echo

clean:
	@rm -f $(OBJECTS)
	@echo "\033[1;31m$(NAME) cleaned\033[0m"

fclean: libclean clean
	@rm -f $(NAME)

libclean:
	@$(MAKE) -C ./lib/libft fclean

re: fclean space all

space:
	@echo

%.o: %.c $(INCLUDES)
	cc -c -o $@ $< $(CFLAGS) $(DEPS)

.PHONY: clean fclean re all libclean space
