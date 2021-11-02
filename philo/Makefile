CC = gcc
CLAGC = -Wall -Wextra -Werror
NAME = philo
RM = rm -f
SRCS = action.c check.c init.c main.c print.c utils.c
OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
all : $(NAME)
clean : 
	$(RM) $(OBJS)
fclean : clean
	$(RM) $(NAME)
re : clean all
.PHONY: all clean fclean re
