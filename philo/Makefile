CC = gcc
CFLAG = -Wall -Wextra -Werror
NAME = philo
RM = rm -f
SRCS = action.c init.c main.c print.c utils.c
OBJS = $(SRCS:.c=.o)
.c.o :
	$(CC) $(CFLAGS) -c -o $@ $<
$(NAME) : $(OBJS)
	ar rcs $@ $^
all : $(NAME)
clean:
	$(RM) $(OBJS) $(BOBJS)
fclean:	clean
	$(RM) $(NAME)
re : clean all
.PHONY:	all clean fclean re