# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/10 19:36:54 by vlepille          #+#    #+#              #
#    Updated: 2023/03/14 13:47:51 by vlepille         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT_NAME := client
SERVER_NAME := server
BONUS_CLIENT_NAME := client_bonus
BONUS_SERVER_NAME := server_bonus

CC := cc

FLAGS := -Wall -Werror -Wextra

INCLUDES := -Ilibft -Iincludes

LIBRARIES := -Llibft -lft

SOURCES_DIR := src

BINARIES_DIR := bin

CLIENT_OBJ := client.o
SERVER_OBJ := server.o

CLIENT_OBJ := $(addprefix $(BINARIES_DIR)/,$(CLIENT_OBJ))
SERVER_OBJ := $(addprefix $(BINARIES_DIR)/,$(SERVER_OBJ))

BONUS_CLIENT_OBJ := client_bonus.o
BONUS_SERVER_OBJ := server_bonus.o

BONUS_CLIENT_OBJ := $(addprefix $(BINARIES_DIR)/,$(BONUS_CLIENT_OBJ))
BONUS_SERVER_OBJ := $(addprefix $(BINARIES_DIR)/,$(BONUS_SERVER_OBJ))

RM := rm -f

all : $(CLIENT_NAME) $(SERVER_NAME)

bonus : $(BONUS_CLIENT_NAME) $(BONUS_SERVER_NAME)

$(CLIENT_NAME) : $(CLIENT_OBJ)
	make -C libft
	$(CC) $(CLIENT_OBJ) $(LIBRARIES) -o $(CLIENT_NAME)

$(SERVER_NAME) : $(SERVER_OBJ)
	make -C libft
	$(CC) $(SERVER_OBJ) $(LIBRARIES) -o $(SERVER_NAME)

$(BONUS_CLIENT_NAME) : $(BONUS_CLIENT_OBJ)
	make -C libft
	$(CC) $(BONUS_CLIENT_OBJ) $(LIBRARIES) -o $(BONUS_CLIENT_NAME)

$(BONUS_SERVER_NAME) : $(BONUS_SERVER_OBJ)
	make -C libft
	$(CC) $(BONUS_SERVER_OBJ) $(LIBRARIES) -o $(BONUS_SERVER_NAME)

$(BINARIES_DIR) :
	mkdir $(BINARIES_DIR)

$(BINARIES_DIR)/%.o : $(SOURCES_DIR)/%.c | $(BINARIES_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean :
	make -C libft clean
	$(RM) $(CLIENT_OBJ) $(SERVER_OBJ) $(BONUS_CLIENT_OBJ) $(BONUS_SERVER_OBJ)

fclean : clean
	make -C libft fclean
	$(RM) $(CLIENT_NAME) $(SERVER_NAME) $(BONUS_CLIENT_NAME) $(BONUS_SERVER_NAME)

re : fclean all

.PHONY: all clean fclean re
