CLIENT_NAME := client
SERVER_NAME := server

CC := cc

FLAGS := -Wall -Werror -Wextra

INCLUDES := -Isrc

LIBRARIES :=

SOURCES_DIR := src

BINARIES_DIR := bin

CLIENT_SRC := client_main.c
SERVER_SRC := client_main.c

CLIENT_OBJ := $(CLIENT_SRC:.c=.o)
SERVER_OBJ := $(SERVER_SRC:.c=.o)

CLIENT_SRC := $(addprefix $(SOURCES_DIR)/,$(CLIENT_SRC))
CLIENT_OBJ := $(addprefix $(BINARIES_DIR)/,$(CLIENT_OBJ))
SERVER_SRC := $(addprefix $(SOURCES_DIR)/,$(SERVER_SRC))
SERVER_OBJ := $(addprefix $(BINARIES_DIR)/,$(SERVER_OBJ))

CLIENT_HEADERS := client.h
SERVER_HEADERS := server.h
CLIENT_HEADERS := $(addprefix $(SOURCES_DIR)/,$(CLIENT_HEADERS))
SERVER_HEADERS := $(addprefix $(SOURCES_DIR)/,$(SERVER_HEADERS))

RM := rm -f

$(CLIENT_NAME) : $(CLIENT_OBJ)
	$(CC) $(CLIENT_OBJ) $(LIBRARIES) -o $(CLIENT_NAME)

$(SERVER_NAME) : $(SERVER_OBJ)
	$(CC) $(SERVER_OBJ) $(LIBRARIES) -o $(SERVER_NAME)

$(BINARIES_DIR) :
	mkdir $(BINARIES_DIR)
# @TODO rm -g3
$(BINARIES_DIR)/%.o : $(SOURCES_DIR)/%.c $(CLIENT_HEADERS) $(SERVER_HEADERS) | $(BINARIES_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@ -g3

all : $(CLIENT_NAME) $(SERVER_NAME)

clean :
	$(RM) $(CLIENT_OBJ) $(SERVER_OBJ)

fclean : clean
	$(RM) $(CLIENT_NAME) $(SERVER_NAME)

re : fclean all

.PHONY: all clean fclean re
