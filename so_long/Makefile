NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I./include -I./mlx -I./libft -I./get_next_line
MLXFLAGS = -L./mlx -lmlx -lXext -lX11 -lm

MLX_PATH = ./mlx
MLX_LIB = $(MLX_PATH)/libmlx.a

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

GNL_PATH = ./get_next_line
GNL_SRCS = $(GNL_PATH)/get_next_line.c $(GNL_PATH)/get_next_line_utils.c
GNL_OBJS = $(GNL_PATH)/get_next_line.o $(GNL_PATH)/get_next_line_utils.o

SRC_PATH = ./src
SRCS = $(SRC_PATH)/main.c \
       $(SRC_PATH)/parse_map.c \
       $(SRC_PATH)/validate_map.c \
       $(SRC_PATH)/map_init.c \
       $(SRC_PATH)/map_reader.c \
       $(SRC_PATH)/extension_check.c \
       $(SRC_PATH)/validate_utils.c \
       $(SRC_PATH)/check_path.c \
       $(SRC_PATH)/render.c \
       $(SRC_PATH)/input.c \
       $(SRC_PATH)/game_utils.c \
       $(SRC_PATH)/utils.c

OBJS = $(SRC_PATH)/main.o \
       $(SRC_PATH)/parse_map.o \
       $(SRC_PATH)/validate_map.o \
       $(SRC_PATH)/map_init.o \
       $(SRC_PATH)/map_reader.o \
       $(SRC_PATH)/extension_check.o \
       $(SRC_PATH)/validate_utils.o \
       $(SRC_PATH)/check_path.o \
       $(SRC_PATH)/render.o \
       $(SRC_PATH)/input.o \
       $(SRC_PATH)/game_utils.o \
       $(SRC_PATH)/utils.o

all: $(MLX_LIB) $(LIBFT) $(NAME)

$(MLX_LIB):
	make -C $(MLX_PATH)

$(LIBFT):
	make -C $(LIBFT_PATH)

$(NAME): $(OBJS) $(GNL_OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(GNL_OBJS) $(LIBFT) $(MLXFLAGS) -o $(NAME)

$(SRC_PATH)/main.o: $(SRC_PATH)/main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SRC_PATH)/parse_map.o: $(SRC_PATH)/parse_map.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SRC_PATH)/validate_map.o: $(SRC_PATH)/validate_map.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SRC_PATH)/map_init.o: $(SRC_PATH)/map_init.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SRC_PATH)/map_reader.o: $(SRC_PATH)/map_reader.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SRC_PATH)/extension_check.o: $(SRC_PATH)/extension_check.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SRC_PATH)/validate_utils.o: $(SRC_PATH)/validate_utils.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SRC_PATH)/check_path.o: $(SRC_PATH)/check_path.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SRC_PATH)/render.o: $(SRC_PATH)/render.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SRC_PATH)/input.o: $(SRC_PATH)/input.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SRC_PATH)/game_utils.o: $(SRC_PATH)/game_utils.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SRC_PATH)/utils.o: $(SRC_PATH)/utils.c
	$(CC) $(CFLAGS) -c $< -o $@

$(GNL_PATH)/get_next_line.o: $(GNL_PATH)/get_next_line.c
	$(CC) $(CFLAGS) -c $< -o $@

$(GNL_PATH)/get_next_line_utils.o: $(GNL_PATH)/get_next_line_utils.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(GNL_OBJS)
	make -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
