CLIENT_NAME := client
SERVER_NAME := server

CC := cc

FLAGS := -Wall -Werror -Wextra

INCLUDES := -Isrc -Ilibft

LIBRARIES := -Llibft -lft

SOURCES_DIR := src

BINARIES_DIR := bin

CLIENT_SRC := client.c
SERVER_SRC := server.c

CLIENT_OBJ := $(CLIENT_SRC:.c=.o)
SERVER_OBJ := $(SERVER_SRC:.c=.o)

CLIENT_SRC := $(addprefix $(SOURCES_DIR)/,$(CLIENT_SRC))
CLIENT_OBJ := $(addprefix $(BINARIES_DIR)/,$(CLIENT_OBJ))
SERVER_SRC := $(addprefix $(SOURCES_DIR)/,$(SERVER_SRC))
SERVER_OBJ := $(addprefix $(BINARIES_DIR)/,$(SERVER_OBJ))

CLIENT_HEADERS :=
SERVER_HEADERS := server.h
CLIENT_HEADERS := $(addprefix $(SOURCES_DIR)/,$(CLIENT_HEADERS))
SERVER_HEADERS := $(addprefix $(SOURCES_DIR)/,$(SERVER_HEADERS))

RM := rm -f

all : $(CLIENT_NAME) $(SERVER_NAME)

bonus : all

$(CLIENT_NAME) : $(CLIENT_OBJ)
	make -C libft
	$(CC) $(CLIENT_OBJ) $(LIBRARIES) -o $(CLIENT_NAME)

$(SERVER_NAME) : $(SERVER_OBJ)
	make -C libft
	$(CC) $(SERVER_OBJ) $(LIBRARIES) -o $(SERVER_NAME)

$(BINARIES_DIR) :
	mkdir $(BINARIES_DIR)
# @TODO rm -g3
$(BINARIES_DIR)/%.o : $(SOURCES_DIR)/%.c $(CLIENT_HEADERS) $(SERVER_HEADERS) | $(BINARIES_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@ -g3

clean :
	make -C libft clean
	$(RM) $(CLIENT_OBJ) $(SERVER_OBJ)

fclean : clean
	make -C libft fclean
	$(RM) $(CLIENT_NAME) $(SERVER_NAME)

re : fclean all

.PHONY: all clean fclean re
