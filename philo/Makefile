NAME = prog
SRC = philo/philo.c philo/utils.c philo/time_utils.c philo/init.c
OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra


all: $(NAME)
	./$(NAME) 2 400 200 200

l:
	leaks --atExit -- ./$(NAME) 2 400 200 200

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)