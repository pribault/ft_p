SERVER = server
CLIENT = client
EXT = Makefile
LIBFT = libft
LIBSOCKET = libsocket

.PHONY: all clean fclean re norme $(LIBFT) $(LIBSOCKET) $(SERVER) $(CLIENT)

all: $(SERVER) $(CLIENT)

$(LIBFT):
	@make -C $(LIBFT)

$(LIBSOCKET):
	@make -C $(LIBSOCKET)

$(SERVER): $(LIBFT) $(LIBSOCKET)
	@make -f $(SERVER).$(EXT)

$(CLIENT): $(LIBFT) $(LIBSOCKET)
	@make -f $(CLIENT).$(EXT)

clean:
	@make -C $(LIBFT) clean
	@make -C $(LIBSOCKET) clean
	@make -f $(SERVER).$(EXT) clean
	@make -f $(CLIENT).$(EXT) clean

fclean:
	@make -C $(LIBFT) fclean
	@make -C $(LIBSOCKET) fclean
	@make -f $(SERVER).$(EXT) fclean
	@make -f $(CLIENT).$(EXT) fclean

re: fclean all

norme:
	@make -C $(LIBFT) norme
	@make -C $(LIBSOCKET) norme
	@make -f $(SERVER).$(EXT) norme
	@make -f $(CLIENT).$(EXT) norme
