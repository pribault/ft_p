NAME = libsocket.a
LIBSO = $(NAME:%.a=%.so)
CC = clang
SRC =	client_new.c\
		client_connect.c\
		client_disconnect.c\
		client_set_callback.c\
		client_poll_events.c\
		client_get_incoming_message.c\
		client_manage_write_requests.c\
		client_enqueue_write_by_fd.c
DIR = client
SRC_DIR = src
OBJ_DIR = .obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/$(DIR)/%.o)
FLAGS = -Wall -Wextra -Werror
INCLUDES =	client.h
INCLUDE = $(INCLUDES:%.h=include/%.h)
N = 0
MAX = $(words $(OBJ))
COMPILED = false
LIBFT = ../libft
LIBFT_INC_DIR = $(LIBFT)/include
LIBFT_INCLUDES =	libft.h\
					ft_printf.h\
					ft_joinf.h\
					malloc.h\
					prototypes.h\
					structs.h
DEPENDENCIES =	$(LIBFT_INCLUDES:%.h=$(LIBFT_INC_DIR)/%.h)

.PHONY: clean fclean all re norme

.SILENT:

all: $(NAME)
	@if [ $(COMPILED) = true ]; then echo "\033[0m\033[38;5;166m[$(DIR) ∎∎∎∎] \033[0m🐹  \033[38;5;214m$(NAME) done\033[0m"; else echo "\033[0m\033[38;5;166m[$(DIR) ∎∎∎∎] \033[0m🐹  \033[38;5;214mnothing to be done\033[0m"; fi

$(OBJ_DIR):
	@mkdir $@

$(OBJ_DIR)/$(DIR): | $(OBJ_DIR)
	@mkdir $@

$(OBJ_DIR)/$(DIR)/%.o: $(SRC_DIR)/$(DIR)/%.c $(INCLUDE) $(DEPENDENCIES) | $(OBJ_DIR)/$(DIR)
	@$(CC) $(FLAGS) -fPIC -I include -I $(LIBFT_INC_DIR) -o $@ -c $<
	@$(eval N=$(shell echo $$(($(N)+1))))
	@$(eval PERCENT=$(shell echo $$((($(N)*100)/$(MAX)))))
	@printf "\033[0m\033[38;5;166m[$(DIR) \033[38;5;7m%3u%%\033[38;5;166m] \033[0m🌶  \033[38;5;226m$(@:$(OBJ_DIR)/$(DIR)/%.o=%.o) done\033[0m\n" $(PERCENT)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@$(eval COMPILED=true)

clean:
	@rm -rf $(OBJ_DIR)/$(DIR)
	@echo "\033[0m\033[38;5;166m[$(DIR) ∎∎∎∎] \033[0m\033[38;5;45mobject files removed\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0m\033[38;5;166m[$(DIR) ∎∎∎∎] \033[0m\033[38;5;87m$(NAME) and $(LIBSO) removed\033[0m"

norme:
	@norminette $(OBJ:$(OBJ_DIR)/%.o=$(SRC_DIR)/%.c) $(INCLUDE)

re: fclean all
