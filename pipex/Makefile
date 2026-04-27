CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex
HEADER = include/pipex.h

SRCDIR = src
INCDIR = include
LIBFTDIR = $(SRCDIR)/libft

HEADERS = -I$(INCDIR) -I$(LIBFTDIR)

SRCS = $(SRCDIR)/main.c \
       $(SRCDIR)/child_exec.c \
       $(SRCDIR)/parent.c \
       $(SRCDIR)/path_utils.c \
       $(SRCDIR)/memory_utils.c \
       $(SRCDIR)/parse_command.c \
       $(SRCDIR)/utils.c \
       $(LIBFTDIR)/ft_split.c \
       $(LIBFTDIR)/ft_strchr.c \
       $(LIBFTDIR)/ft_strdup.c \
       $(LIBFTDIR)/ft_strjoin.c \
       $(LIBFTDIR)/ft_strlcpy.c \
       $(LIBFTDIR)/ft_strlen.c \
       $(LIBFTDIR)/ft_strncmp.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(HEADERS) -o $@ $(OBJS)

$(SRCDIR)/main.o: $(SRCDIR)/main.c $(HEADER)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(SRCDIR)/child_exec.o: $(SRCDIR)/child_exec.c $(HEADER)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(SRCDIR)/parent.o: $(SRCDIR)/parent.c $(HEADER)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(SRCDIR)/path_utils.o: $(SRCDIR)/path_utils.c $(HEADER)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(SRCDIR)/memory_utils.o: $(SRCDIR)/memory_utils.c $(HEADER)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(SRCDIR)/parse_command.o: $(SRCDIR)/parse_command.c $(HEADER)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(SRCDIR)/utils.o: $(SRCDIR)/utils.c $(HEADER)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(LIBFTDIR)/ft_putendl_fd.o: $(LIBFTDIR)/ft_putendl_fd.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(LIBFTDIR)/ft_putstr_fd.o: $(LIBFTDIR)/ft_putstr_fd.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(LIBFTDIR)/ft_split.o: $(LIBFTDIR)/ft_split.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(LIBFTDIR)/ft_strchr.o: $(LIBFTDIR)/ft_strchr.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(LIBFTDIR)/ft_strdup.o: $(LIBFTDIR)/ft_strdup.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(LIBFTDIR)/ft_strjoin.o: $(LIBFTDIR)/ft_strjoin.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(LIBFTDIR)/ft_strlcpy.o: $(LIBFTDIR)/ft_strlcpy.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(LIBFTDIR)/ft_strlen.o: $(LIBFTDIR)/ft_strlen.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(LIBFTDIR)/ft_strncmp.o: $(LIBFTDIR)/ft_strncmp.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
