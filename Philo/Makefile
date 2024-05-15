NAME = philo

CC = cc 
CFLAGS = -Wall -Wextra -Werror

INC = philosophers.h

SRC = 	philosophers.c \
		philo_utils.c \
		philo_utils_2.c \
		time_eat.c 

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):$(OBJ) $(INC) clean
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	@rm -rf $(OBJ)
fclean: clean
	@rm -rf $(NAME)

re: fclean all