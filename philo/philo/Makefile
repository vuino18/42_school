NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude
RM = rm -f

SRCS = src/main.c \
       src/utils.c \
       src/clean.c \
       src/init.c \
       src/monitor_routine.c \
       src/routine.c \
       src/utils_time.c

OBJS = $(SRCS:.c=.o)

HDR = include/philo.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS): $(HDR)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
