NAME = libsocket.a
LIBSO = $(NAME:%.a=%.so)
MAKE_DIR = .Makefiles
OBJ_DIR = .obj
CLIENT = client
SERVER = server
TEST = test
EXT = Makefile

.PHONY: clean fclean all re norme $(NAME) $(LIBSO) $(CLIENT) $(SERVER)

.SILENT:

$(NAME): $(CLIENT) $(SERVER)

$(LIBSO): $(NAME)
	@$(eval OBJ=$(shell ar t $(NAME)))
	@ar x $(NAME)
	@$(CC) -o $@ -shared $(OBJ)
	@rm $(OBJ)
	@echo "\033[0m\033[38;5;166m[$@ ∎∎∎∎] \033[0m🐹  \033[38;5;214mdone\033[0m"

$(CLIENT):
	@make -f $(MAKE_DIR)/$(CLIENT).$(EXT)

$(SERVER):
	@make -f $(MAKE_DIR)/$(SERVER).$(EXT)

$(TEST): $(NAME)
	@make -f $(MAKE_DIR)/$(TEST).$(EXT)

all: $(NAME)

clean:
	@make -f $(MAKE_DIR)/$(CLIENT).$(EXT) clean
	@make -f $(MAKE_DIR)/$(SERVER).$(EXT) clean

fclean:
	@make -f $(MAKE_DIR)/$(CLIENT).$(EXT) fclean
	@make -f $(MAKE_DIR)/$(SERVER).$(EXT) fclean
	@make -f $(MAKE_DIR)/$(TEST).$(EXT) fclean
	@rm -f $(LIBSO)

norme:
	@make -f $(MAKE_DIR)/$(CLIENT).$(EXT) norme
	@make -f $(MAKE_DIR)/$(SERVER).$(EXT) norme

re:
	@make -f $(MAKE_DIR)/$(CLIENT).$(EXT) re
	@make -f $(MAKE_DIR)/$(SERVER).$(EXT) re
