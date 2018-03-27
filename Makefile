SERVER = server
CLIENT = client
EXT = Makefile
LIBFT = libft
LIBSOCKET = libsocket
JOBS = 1

.PHONY: all clean fclean re norme $(LIBFT) $(LIBSOCKET)

all: $(SERVER) $(CLIENT)

$(LIBFT):
	@make -C $(LIBFT) -j$(JOBS)

$(LIBSOCKET):
	@make -C $(LIBSOCKET) -j$(JOBS)

$(SERVER): $(LIBFT) $(LIBSOCKET)
	@make -f $(SERVER).$(EXT) -j$(JOBS)

$(CLIENT): $(LIBFT) $(LIBSOCKET)
	@make -f $(CLIENT).$(EXT) -j$(JOBS)

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
