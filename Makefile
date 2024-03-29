CFLAGS= -Wextra -Wall -Werror -MMD
DEBUG_CFLAGS= $(CFLAGS) -g -fsanitize=address
LIBS	:= -lft -L./lib/libft
NAME = minishell
OBJECTS = src/main.o src/ft_split_quote.o src/minishell_utils.o src/sig_center.o src/sig_meta.o src/ft_strcmp.o \
	src/path_parsing.o src/child_process.o src/execute.o \
	src/b_pwd.o	src/b_echo.o src/b_env.o src/b_export.o src/b_unset.o src/b_cd.o src/b_exit.o src/b_builtin.o \
	src/here_doc.o	src/redirections.o	src/here_doc_utils.o src/env_utils.o src/env.o src/exec_env.o \
	src/parsing_operators.o	src/parsing_quotes.o src/parsing_operators_start.o src/error_func.o \
	src/exec_cmds.o src/parsing_env_var.o src/parsing_env_var_len.o src/parsing_env_utils.o \
	src/b_export_utils.o src/error_func_2.o	src/parent_process.o	src/redirections_utils.o	src/innit_func.o src/parse_error.o	src/main_utils.o
DEPS = -I./include -I./lib/libft -I/Users/$(USER)/.brew/opt/readline/include
READLINE_LIB = -L/Users/$(USER)/.brew/opt/readline/lib -lreadline -lhistory
INCLUDES = $(OBJECTS:.o=.d)


all: space lib/libft/libft.a
	@echo "\033[1;32mMaking libft:\033[0m"
	@$(MAKE) -C ./lib/libft 2>&1 | (grep -v "make\[[0-9]*\]" || echo "\033[1;33mNothing to be done for libft\033[0m\n")
	@echo "\033[1;32mMaking $(NAME):\033[0m"
	@$(MAKE) $(NAME) 2>&1 | (grep -v "make\[[0-9]*\]" || echo "\033[1;33mNothing to be done for $(NAME)\033[0m\n")

lib/libft/libft.a:
	@if [ ! -d /Users/$(USER)/.brew ]; then \
        echo "\033[1;32mInstalling brew:\033[0m"; \
        curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh; \
        echo "\033[1;32mBrew installed\033[0m"; \
    fi
	brew install readline

$(NAME): $(OBJECTS)
	@echo
	$(CC) $(OBJECTS) $(LIBS) -o $(NAME) $(CFLAGS) $(DEPS) $(READLINE_LIB)
	@echo "\033[1;32m$(NAME) compiled\033[0m"
	@echo

debug:
	@$(MAKE) all CFLAGS="$(DEBUG_CFLAGS)"

redebug: clean debug

update: clean all

clean:
	@rm -f $(OBJECTS) $(INCLUDES)
	@rm -rf minishell.dSYM
	@echo "\033[1;31m$(NAME) cleaned\033[0m"

fclean: libclean clean
	@rm -f $(NAME)

libclean:
	@$(MAKE) -C ./lib/libft fclean
	@echo "\033[1;31mlibft cleaned\033[0m"

re: fclean space all

space:
	@echo

%.o: %.c
	cc -c -o $@ $< $(CFLAGS) $(DEPS)

.PHONY: clean fclean re all libclean space update debug

-include $(INCLUDES)
