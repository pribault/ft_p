#include "client.h"

void		my_exit(void)
{
	ft_putstr("exiting...\n");
}

t_client	*init_client(void)
{
	static t_client	client;

	ft_bzero(&client, sizeof(t_client));
	client.socket = -1;
	client.protocol = TCP;
	client.port = 4242;
	return (&client);
}

int			main(int argc, char **argv)
{
	t_client	*client;

	atexit(&my_exit);
	client = init_client();
	get_flags(client, argc, argv);
	connect_to_server(client);
	return (0);
}
