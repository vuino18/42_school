CC      = cc
FLAGS   = -Wall -Wextra -Werror
AR      = ar rcs
RM      = rm -f

NAME    = libftprintf.a
HEADER  = ft_printf.h

SRCS = \
       ft_printf.c \
       ft_putchar.c \
       ft_putnbr.c \
       ft_putstr.c \
       ft_puthex.c \
       ft_putuint.c \
       ft_putpct.c \
       ft_putptr.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

ft_printf.o: ft_printf.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

ft_putchar.o: ft_putchar.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

ft_putnbr.o: ft_putnbr.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

ft_putstr.o: ft_putstr.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

ft_puthex.o: ft_puthex.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

ft_putuint.o: ft_putuint.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

ft_putpct.o: ft_putpct.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

ft_putptr.o: ft_putptr.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

