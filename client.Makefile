NAME = client
CC = clang
FLAGS = -Wall -Wextra
LIBFT = libft
INC_DIR = include
INCLUDES = client.h
INCLUDE = $(INCLUDES:%.h=$(INC_DIR)/%.h)
SRC_DIR = src/client
SRC =	main.c flags.c error.c client.c\
		connect.c
OBJ = $(SRC:%.c=$(SRC_DIR)/%.o)

.PHONY: all clean fclean re norme nl

all: $(NAME)

%.o: %.c $(INCLUDE)
	@echo "\033[0m\033[38;5;214mcompiling $@\033[0m"
	@$(CC) $(FLAGS) -I $(INC_DIR) -I $(LIBFT)/$(INC_DIR) -o $@ -c $<
	@echo "\033[1A\033[K\033[0m\033[38;5;214m$@ compiled\033[0m"

$(NAME): $(OBJ) $(LIBFT)/libft.a
	@echo "\033[0m\033[38;5;124m\033[1mcompiling $@\033[0m"
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ) -L $(LIBFT) -lft
	@echo "\033[1A\033[K\033[0m\033[38;5;124m\033[1m$@ compiled\033[0m"

clean:
	@echo "\033[0m\033[38;5;123mremoving object files\033[0m"
	@rm -f $(OBJ)
	@echo "\033[1A\033[K\033[0m\033[38;5;123mobject files removed\033[0m"

fclean: clean
	@echo "\033[0m\033[38;5;14mremoving $(NAME)\033[0m"
	@rm -f $(NAME)
	@echo "\033[1A\033[K\033[0m\033[38;5;14m$(NAME) removed\033[0m"

re: fclean all

norme:
