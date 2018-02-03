NAME = server
CC = clang
FLAGS = -Wall -Wextra
INC = include
INCLUDE = server.h protocol.h
INCLUDES = $(INCLUDE:%.h=$(INC)/%.h)
OBJ = src/server_obj
SRC = src/server
SRCS =	server.c flags.c flags_2.c\
		clients.c message.c commands.c\
		receive.c handle_message.c\
		handle_message_2.c
OBJS = $(SRCS:%.c=$(OBJ)/%.o)
LIBFT = libft
LIBSOCKET = libsocket
INCLUDE_LIBS = -I $(LIBFT)/include -I $(LIBSOCKET)/include
COMPILE_LIBS = -L $(LIBSOCKET) -lsocket -L $(LIBFT) -lft
JOBS = 4

.PHONY: all clean fclean re export

all: $(NAME)

$(OBJ):
	@mkdir $@

$(LIBFT)/libft.a:

$(OBJ)%.o: $(SRC)%.c $(INCLUDES) $(LIBFT)/libft.a | $(OBJ)
	@echo "\033[38;5;207m🍇  compiling $@\033[0m"
	@$(CC) $(FLAGS) -I $(INC) $(INCLUDE_LIBS) -o $@ -c $<
	@echo "\033[1A\033[K\033[38;5;207m🍇  $@ done\033[0m"

$(NAME): $(OBJS)
	@echo "\033[38;5;125m🐼  compiling $(NAME)\033[0m"
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(COMPILE_LIBS)
	@echo "\033[1A\033[K\033[38;5;125m🐼  $(NAME) done\033[0m"

clean:
	@rm -rf $(OBJ)
	@echo "\033[0m\033[38;5;45mobject files removed\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0m\033[38;5;87m$(NAME) removed\033[0m"

norme:
	@norminette $(OBJS:%.o=%.c) $(INCLUDES)

re: fclean all
