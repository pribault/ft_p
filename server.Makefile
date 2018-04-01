NAME = server
CC = clang
FLAGS = -Wall -Wextra -Werror
INC = include
INCLUDE = server.h protocol.h
INCLUDES = $(INCLUDE:%.h=$(INC)/%.h)
OBJ = src/server_obj
SRC = src/server
SRCS =	server.c flags.c flags_2.c\
		clients.c message.c commands.c\
		receive.c handle_message.c\
		handle_message_2.c handle_message_3.c
OBJS = $(SRCS:%.c=$(OBJ)/%.o)
LIBFT = libft
LIBSOCKET = libsocket
INCLUDE_LIBS = -I $(LIBFT)/include -I $(LIBSOCKET)/include
COMPILE_LIBS = -L $(LIBSOCKET) -lsocket -L $(LIBFT) -lft
JOBS = 1
COMPILED = false

.PHONY: all clean fclean re export

all: $(NAME)
	@if [ $(COMPILED) = true ]; then echo "\033[38;5;125m🐼  $(NAME) done\033[0m"; else echo "\033[38;5;125m🐼  nothing to be done for $(NAME)\033[0m"; fi

$(OBJ):
	@mkdir $@

$(LIBFT)/libft.a:

$(LIBSOCKET)/libsocket.a:

$(OBJ)/%.o: $(SRC)/%.c $(INCLUDES) $(LIBFT)/libft.a $(LIBSOCKET)/libsocket.a | $(OBJ)
	@$(CC) $(FLAGS) -I $(INC) $(INCLUDE_LIBS) -o $@ -c $<
	@echo "\033[38;5;207m🍇  $@ done\033[0m"

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(COMPILE_LIBS)
	@$(eval COMPILED=true)

clean:
	@rm -rf $(OBJ)
	@echo "\033[0m\033[38;5;45mobject files removed\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0m\033[38;5;87m$(NAME) removed\033[0m"

norme:
	@norminette $(OBJS:$(OBJ)/%.o=$(SRC)/%.c) $(INCLUDES)

re: fclean all
