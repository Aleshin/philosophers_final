CC = gcc -pthread -fsanitize=thread -g
CFLAGS = -Wall -Wextra -Werror

SRC = philo.c init.c init_threads.c monitor.c routine.c utils.c
OBJ_DIR = OBJ
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
NAME = philo

all: $(NAME)

$(NAME): $(OBJ) Makefile
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: %.c Makefile philo.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean : 
	rm -r $(OBJ_DIR)

fclean :
	rm -f $(NAME)
	rm -r $(OBJ_DIR)

re : fclean all

.PHONY : clean fclean re all
