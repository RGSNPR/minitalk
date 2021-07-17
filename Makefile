SERVER = server

CLIENT = client

LIBFT = libft.a

CC = gcc

CFLAGS = -g

RM = rm -f

INCL = philo_one.h

SRC_SERVER = server.c init_struct.c exit_error.c

SRC_CLIENT = client.c exit_error.c

OBJ_SRV = $(SRC_SERVER:.c=.o)

OBJ_CLT = $(SRC_CLIENT:.c=.o)


all: $(LIBFT) $(SERVER) $(CLIENT)

$(LIBFT):
	@make -C libft

$(SERVER): $(OBJ_SRV)
	@$(CC) $(CFLAGS) -o $(SERVER) $(SRC_SERVER) -L./libft -lft
	@printf "$@ built successfully!\n"

$(CLIENT): $(OBJ_CLT)
	@$(CC) $(CFLAGS) -o $(CLIENT) $(SRC_CLIENT) -L./libft -lft
	@printf "$@ built successfully!\n"


clean:
	@make clean -C libft
	@$(RM) $(OBJ_SRV) $(OBJ_CLT)

fclean: clean
	@make fclean -C libft
	@$(RM) $(SERVER) $(CLIENT)
	@printf "\e[38;5;46mall clear :)\e[0m\n"

re: fclean all

.PHONY: clean fclean all re bonus
