CC = clang
FLAGS = -Wall -Wextra -Ofast
SRC =	basic_server.c\
		basic_client.c
BIN = $(SRC:%.c=.bin/%.out)
LIBFT = ../libft

.PHONY: fclean re $(LIBFT)/libft.a

all: $(BIN)

$(LIBFT)/libft.a:
	@make -C $(LIBFT)

%.out: %.c $(LIBFT)/libft.a libsocket.a
	@$(CC) $(FLAGS) -o $@ $< -I include -I $(LIBFT)/include -L . -lsocket -L $(LIBFT) -lft 
	@echo "\033[0m🐧  \033[38;5;33m$@ done\033[0m"

fclean:
	@rm -f $(BIN)
	@if [ -e $(LIBFT)/libft.a ]; then make -C $(LIBFT) fclean; fi;

re: fclean all
