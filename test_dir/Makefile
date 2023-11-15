NAME = prog

CC = cc
# CFLAGS = -Wall -Werror -Wextra
CFLAGS = 

# SRC = 03_race_condition.c
# SRC = 04_mutex.c
# SRC = 05_loop_thread.c
# SRC = 06_get_value_from_thread.c
# SRC = 07_pass_arg.c
# SRC = 08_basic_use.c
# SRC = 10_condition_variable.c
# SRC = 11_condition_signal.c
# SRC = 12_try_lock.c
# SRC = 14_barriers.c
# SRC = 17_detach.c
# SRC = 18_static_initializers.c
# SRC = 19_deadlock.c 
SRC = 20_semaphore.c 

all: clean $(NAME)
	./$(NAME)

l:
	leaks --atExit -- ./$(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -f $(NAME)

# re: clean all
