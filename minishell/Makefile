NAME    = minishell

CC      = cc
CFLAGS  = -Wall -Wextra -Werror
INCS    = -I./include -I./libft
HEADER	= include/minishell.h
LIBFT   = ./libft/libft.a
LIBFT_H = ./libft/libft.h

SRC     = src/main.c \
          src/shell_loop.c \
          src/execute.c \
          src/fork_utils.c \
          src/builtin_dispatch.c \
          src/env_node.c \
          src/env_list.c \
          src/env_convert.c \
          src/path_utils.c \
          src/pipes.c \
          src/redirs.c \
          src/heredoc.c \
          src/signals.c \
          src/lexer.c \
          src/expand.c \
          src/parse_utils.c \
          src/parser.c \
          src/builtins/echo.c \
          src/builtins/cd.c \
          src/builtins/pwd.c \
          src/builtins/env.c \
          src/builtins/export.c \
          src/builtins/unset.c \
          src/builtins/exit.c \
	  src/builtins/exit_utils.c \
	  src/execute_path.c \
	  src/execute_utils.c \
	  src/expand_hd.c \
	  src/heredoc_child.c \
	  src/lexer_ops.c \
	  src/parser_build.c \
	  src/parser_utils.c \
	  src/shell_utils.c

OBJ     = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT): FORCE
	$(MAKE) -C libft

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

$(OBJ): $(HEADER) $(LIBFT) $(LIBFT_H)

%.o: %.c $(HEADER) $(LIBFT_H)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all

FORCE:
.PHONY: all clean fclean re FORCE
