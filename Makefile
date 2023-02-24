SERVER = server
CLIENT = client

CC 				=	gcc
CFLAGS 			=	-Wall -Wextra -Werror
INCLUDES_DIR 	=	include/
SRC_DIR 		=	src/
OBJ_DIR 		=	obj/
INCLUDES_H		=	-I./$(INCLUDES_DIR)
DEPS 			=

COMMON_SRC		=	$(addprefix common_src/, \
					ft_atoi.c \
					ft_strlen.c \
					ft_putstr.c \
					ft_putchar.c \
					ft_isspace.c \
					)

SERVER_SRC 		= 	$(addprefix server_src/, \
					server.c \
					ft_bzero.c \
					ft_strcat.c \
					ft_putnbr.c \
					ft_malloc.c \
					ft_get_pid.c \
					ft_atoi_base.c \
					ft_strcat_int.c \
					ft_print_and_reset.c \
					ft_strcat_without_end.c \
					)

CLIENT_SRC 		= 	$(addprefix client_src/, \
					client.c \
					ft_error.c \
					ft_memset.c \
					)

SERVER_SRCS		=	$(addprefix $(SRC_DIR), \
					${COMMON_SRC} \
					${SERVER_SRC} \
					)
CLIENT_SRCS 	=	$(addprefix $(SRC_DIR), \
					${COMMON_SRC} \
					${CLIENT_SRC} \
					)

SERVER_OBJ 		=	$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o, $(SERVER_SRCS))
CLIENT_OBJ		=	$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o, $(CLIENT_SRCS))

all: 	$(SERVER) $(CLIENT)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(DEPS)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES_H) -c -o $@ $^

$(SERVER): $(SERVER_OBJ) $(DEPS)
	@echo "\e[36mMaking $(SERVER)...\e[0m"
	@$(CC) $(CFLAGS) $(INCLUDES_H) $(SERVER_OBJ) -o $(SERVER)
	@echo "\e[32mDone !\e[0m"

$(CLIENT): $(CLIENT_OBJ) $(DEPS)
	@echo "\e[36mMaking $(CLIENT)...\e[0m"
	@$(CC) $(CFLAGS) $(INCLUDES_H) $(CLIENT_OBJ) -o $(CLIENT)
	@echo "\e[32mDone !\e[0m"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\e[31mObject files removed.\e[0m"

fclean: clean
	@rm -f $(SERVER)
	@echo "\e[31m$(SERVER) removed.\e[0m"
	@rm -f $(CLIENT)
	@echo "\e[31m$(CLIENT) removed.\e[0m"

re: fclean all

bonus: all

.PHONY: all clean fclean re

