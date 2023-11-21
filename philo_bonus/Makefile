# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/18 12:19:46 by pnamnil           #+#    #+#              #
#    Updated: 2023/11/21 15:54:43 by pnamnil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
SRC = philo_bonus.c check_arg.c utils.c init_philo.c routine.c monitor.c time_utils.c
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
# MY_EXEC = ./$(NAME) 3 119 60 60

HEADER = philo_bonus.h

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
