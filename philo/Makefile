NAME = philo
SRC = philo.c utils.c init.c routine.c mornitor.c time_utils.c
OBJ = $(SRC:.c=.o)

CC = cc
# CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
# CFLAGS = -Wall -Werror -Wextra -g -fsanitize=thread
CFLAGS = -Wall -Werror -Wextra

# MY_EXEC = ./$(NAME) 1 800 200 200
# MY_EXEC = ./$(NAME) 5 800 200 200
# MY_EXEC = ./$(NAME) 5 800 200 200 7
# MY_EXEC = ./$(NAME) 4 410 200 200
MY_EXEC = ./$(NAME) 4 310 200 100

all: $(NAME)
	$(MY_EXEC)

l:
	leaks --atExit -- $(MY_EXEC)

v:
	valgrind $(MY_EXEC)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
