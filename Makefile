#CFLAGS= -g -Wextra -Wall -Werror -fsanitize=address
CFLAGS= -g -Wextra -Wall -Werror
LIBS	:= -lft -L./lib/libft
NAME = minishell
OBJECTS = src/main.o src/ft_split_quote.o src/minishell_utils.o src/sig_center.o src/sig_meta.o src/ft_strcmp.o \
	src/path_parsing.o src/parent_child_process.o src/line_reader.o src/execute.o \
	src/b_pwd.o	src/b_echo.o src/b_env.o src/b_export.o src/b_unset.o src/b_cd.o src/b_exit.o src/b_builtin.o \
	src/here_doc.o	src/redirections.o	src/here_doc_utils.c
DEPS = -I./include -I./lib/libft -I/Users/$(USER)/.brew/opt/readline/include
READLINE_LIB = -L/Users/$(USER)/.brew/opt/readline/lib -lreadline -lhistory
INCLUDES = include/minishell.h


all: space lib/libft/libft.a
	@echo "\033[1;32mMaking libft:\033[0m"
	@$(MAKE) -C ./lib/libft 2>&1 | (grep -v "make\[1\]" || echo "\033[1;33mNothing to be done for libft\033[0m\n")
	@echo "\033[1;32mMaking $(NAME):\033[0m"
	@$(MAKE) $(NAME) 2>&1 | (grep -v "make\[1\]" || echo "\033[1;33mNothing to be done for $(NAME)\033[0m\n")

lib/libft/libft.a:
	brew install readline

$(NAME): $(OBJECTS) $(INCLUDES)
	@echo
	$(CC) $(OBJECTS) $(LIBS) -o $(NAME) $(CFLAGS) $(DEPS) $(READLINE_LIB)
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
