NAME = libsocket.a
LIBSO = $(NAME:%.a=%.so)
CC = clang
SRC =	server_new.c server_delete.c\
		server_start.c server_stop.c\
		server_attach_data.c\
		server_get_data.c\
		server_set_callback.c\
		server_poll_events.c\
		server_add_incoming_client.c\
		server_manage_incoming_messages.c\
		server_manage_write_requests.c\
		server_remove_client.c\
		server_get_client_fd.c\
		server_enqueue_write.c\
		server_enqueue_write_by_fd.c\
		server_add_client_by_fd.c\
		server_get_client_address.c\
		server_client_attach_data.c\
		server_client_get_data.c\
		server_set_queue_max.c\
		server_get_queue_max.c\
		server_set_timeout.c\
		server_get_timeout.c\
		server_get_incoming_message.c\
		server_connect.c\
		server_find_client_by_address.c
DIR = server
SRC_DIR = src
OBJ_DIR = .obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/$(DIR)/%.o)
FLAGS = -Wall -Wextra -Werror
INCLUDES =	server.h
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
	$(eval COMPILED=true)

clean:
	@rm -rf $(OBJ_DIR)/$(DIR)
	@echo "\033[0m\033[38;5;166m[$(DIR) ∎∎∎∎] \033[0m\033[38;5;45mobject files removed\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0m\033[38;5;166m[$(DIR) ∎∎∎∎] \033[0m\033[38;5;87m$(NAME) and $(LIBSO) removed\033[0m"

norme:
	@norminette $(OBJ:$(OBJ_DIR)/%.o=$(SRC_DIR)/%.c) $(INCLUDE)

re: fclean all
