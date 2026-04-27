CC      = cc
CFLAGS  = -Wall -Wextra -Werror
SRC     = .
INC_DIR = .
INC     = -I$(INC_DIR)
AR      = ar rcs
RM      = rm -f

HEADER  = $(SRC)/libft.h
NAME    = libft.a

SRCS = \
	$(SRC)/ft_strlcpy.c \
	$(SRC)/ft_strlen.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(RM) $(NAME)
	$(AR) $(NAME) $(OBJS)

$(SRC)/ft_strlcpy.o: $(SRC)/ft_strlcpy.c $(HEADER)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(SRC)/ft_strlen.o: $(SRC)/ft_strlen.c $(HEADER)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
