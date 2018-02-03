NAME = libsocket.a
LIBSO = $(NAME:%.a=%.so)
CC = clang
CLIENT_SRC =	client_new.c\
				client_connect.c\
				client_disconnect.c\
				client_set_callback.c\
				client_poll_events.c\
				client_get_incoming_message.c\
				client_manage_write_requests.c\
				client_enqueue_write_by_fd.c
SERVER_SRC =	server_new.c server_delete.c\
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
				server_set_clients_max.c\
				server_get_clients_max.c\
				server_bind.c\
				server_unbind.c\
				server_connect.c\
				server_set_timeout.c\
				server_get_timeout.c
SRC =	$(CLIENT_SRC:%.c=client/%.c)\
		$(SERVER_SRC:%.c=server/%.c)
OBJ = $(SRC:%.c=obj/%.o)
FLAGS = -Wall -Wextra
INCLUDES =	libsocket.h client.h server.h
INCLUDE = $(INCLUDES:%.h=include/%.h)
LIBFT = ../libft

.PHONY: clean fclean all re norme

all: $(NAME)

obj:
	@mkdir obj

obj/client: | obj
	@mkdir obj/client

obj/server: | obj
	@mkdir obj/server

obj/client/%.o: src/client/%.c $(INCLUDE) | obj/client
	@$(CC) $(FLAGS) -fPIC -I include -I $(LIBFT)/include -o $@ -c $<
	@echo "\033[0m🌶  \033[38;5;226m$@ done\033[0m"

obj/server/%.o: src/server/%.c $(INCLUDE) | obj/server
	@$(CC) $(FLAGS) -fPIC -I include -I $(LIBFT)/include -o $@ -c $<
	@echo "\033[0m🌶  \033[38;5;226m$@ done\033[0m"

$(LIBSO): $(OBJ)
	@$(CC) $(FLAGS) -shared -o $(LIBSO) $(OBJ)
	@echo "\033[0m🦁  \033[38;5;214m$@ done\033[0m"

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\033[0m🐹  \033[38;5;214m$@ done\033[0m"

clean:
	@rm -rf obj
	@echo "\033[0m\033[38;5;45mobject files removed\033[0m"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBSO)
	@echo "\033[0m\033[38;5;87m$(NAME) and $(LIBSO) removed\033[0m"

norme:
	@norminette $(OBJ:obj/%.o=src/%.c) $(INCLUDE)

re: fclean all
