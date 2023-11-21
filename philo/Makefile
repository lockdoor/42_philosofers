# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/18 12:19:46 by pnamnil           #+#    #+#              #
#    Updated: 2023/11/21 15:54:16 by pnamnil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC = philo.c utils.c check_arg.c init.c routine.c monitor.c time_utils.c
OBJ = $(SRC:.c=.o)

CC = cc
# CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
# CFLAGS = -Wall -Werror -Wextra -g -fsanitize=thread
CFLAGS = -Wall -Werror -Wextra

# MY_EXEC = ./$(NAME) 1 800 200 200
# MY_EXEC = ./$(NAME) 5 800 200 200
# MY_EXEC = ./$(NAME) 5 800 200 200 7
# MY_EXEC = ./$(NAME) 4 410 200 200
# MY_EXEC = ./$(NAME) 4 310 200 100
# MY_EXEC = ./$(NAME) 4 122 60 60 2

HEADER = philo.h

all: $(NAME)

l:
	leaks --atExit -- $(MY_EXEC)

v:
	valgrind $(MY_EXEC)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
