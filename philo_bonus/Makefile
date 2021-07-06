# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyerkim <hyerkim@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/06 21:25:59 by hyerkim           #+#    #+#              #
#    Updated: 2021/07/06 21:27:24 by hyerkim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CLAGC = -Wall -Wextra -Werror
NAME = philo_bonus
RM = rm -f
SRCS = action_bonus.c check_bonus.c init_bonus.c main_bonus.c print_bonus.c utils_bonus.c
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