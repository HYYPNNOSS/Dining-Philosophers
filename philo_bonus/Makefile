NAME = philo_bonus

CC = cc 
CFLAGS = -Wall -Wextra -Werror

INC = philo_bonus.h

SRC = 	main.c \
		philo_utils.c \
		init_philos_bonus.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):$(OBJ) $(INC) clean
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	@rm -rf $(OBJ)
fclean: clean
	@rm -rf $(NAME)

re: fclean all