SERVER = server
CLIENT = client
EXT = Makefile
LIBFT = libft

.PHONY: all clean fclean re norme $(LIBFT)

all: $(SERVER) $(CLIENT)

$(LIBFT):
	@make -C $(LIBFT)

$(SERVER): $(LIBFT)
	@make -f $(SERVER).$(EXT)

$(CLIENT): $(LIBFT)
	@make -f $(CLIENT).$(EXT)

clean:
	@make -C $(LIBFT) clean
	@make -f $(SERVER).$(EXT) clean
	@make -f $(CLIENT).$(EXT) clean

fclean:
	@make -C $(LIBFT) fclean
	@make -f $(SERVER).$(EXT) fclean
	@make -f $(CLIENT).$(EXT) fclean

re: fclean all

norme:
	@make -C $(LIBFT) norme
	@make -f $(SERVER).$(EXT) norme
	@make -f $(CLIENT).$(EXT) norme
