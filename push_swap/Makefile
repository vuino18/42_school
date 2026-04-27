CC      = cc
CFLAGS  = -Wall -Wextra -Werror -Iinclude -Ilibft
RM      = rm -f
NAME    = push_swap
HEADER  = include/push_swap.h

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = \
	src/main.c \
	src/parsing/error_handling.c src/parsing/arg_validation.c src/parsing/ft_atoi_safe.c src/parsing/ft_split.c \
	src/stack/stack_init.c src/stack/stack_utils.c \
	src/operations/push_ops.c src/operations/swap_ops.c src/operations/rotate_ops.c \
	src/operations/revrotate_ops.c src/operations/indexes.c \
	src/sorting/sort_small.c src/sorting/sort_big.c \
	src/utils/ft_utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)
	
$(LIBFT): $(LIBFT_DIR)/*.c $(LIBFT_DIR)/*.h
	$(MAKE) -C $(LIBFT_DIR)

src/main.o: src/main.c $(HEADER)
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

src/parsing/error_handling.o: src/parsing/error_handling.c $(HEADER)
	$(CC) $(CFLAGS) -c src/parsing/error_handling.c -o src/parsing/error_handling.o
	
src/parsing/arg_validation.o: src/parsing/arg_validation.c $(HEADER)
	$(CC) $(CFLAGS) -c src/parsing/arg_validation.c -o src/parsing/arg_validation.o

src/parsing/ft_atoi_safe.o: src/parsing/ft_atoi_safe.c $(HEADER)
	$(CC) $(CFLAGS) -c src/parsing/ft_atoi_safe.c -o src/parsing/ft_atoi_safe.o

src/parsing/ft_split.o: src/parsing/ft_split.c $(HEADER)
	$(CC) $(CFLAGS) -c src/parsing/ft_split.c -o src/parsing/ft_split.o

src/stack/stack_init.o: src/stack/stack_init.c $(HEADER)
	$(CC) $(CFLAGS) -c src/stack/stack_init.c -o src/stack/stack_init.o

src/stack/stack_utils.o: src/stack/stack_utils.c $(HEADER)
	$(CC) $(CFLAGS) -c src/stack/stack_utils.c -o src/stack/stack_utils.o

src/operations/push_ops.o: src/operations/push_ops.c $(HEADER)
	$(CC) $(CFLAGS) -c src/operations/push_ops.c -o src/operations/push_ops.o

src/operations/swap_ops.o: src/operations/swap_ops.c $(HEADER)
	$(CC) $(CFLAGS) -c src/operations/swap_ops.c -o src/operations/swap_ops.o

src/operations/rotate_ops.o: src/operations/rotate_ops.c $(HEADER)
	$(CC) $(CFLAGS) -c src/operations/rotate_ops.c -o src/operations/rotate_ops.o

src/operations/revrotate_ops.o: src/operations/revrotate_ops.c $(HEADER)
	$(CC) $(CFLAGS) -c src/operations/revrotate_ops.c -o src/operations/revrotate_ops.o

src/operations/indexes.o: src/operations/indexes.c $(HEADER)
	$(CC) $(CFLAGS) -c src/operations/indexes.c -o src/operations/indexes.o

src/sorting/sort_small.o: src/sorting/sort_small.c $(HEADER)
	$(CC) $(CFLAGS) -c src/sorting/sort_small.c -o src/sorting/sort_small.o

src/sorting/sort_big.o: src/sorting/sort_big.c $(HEADER)
	$(CC) $(CFLAGS) -c src/sorting/sort_big.c -o src/sorting/sort_big.o

src/utils/ft_utils.o: src/utils/ft_utils.c $(HEADER)
	$(CC) $(CFLAGS) -c src/utils/ft_utils.c -o src/utils/ft_utils.o

clean:
	$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
