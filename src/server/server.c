#include "server.h"

void	get_new_clients(t_server *server)
{
	t_client	client;
	int			fd;

	while (is_input_waiting(server->socket, server->timeout))
	{
		fd = accept(server->socket, &client.addr, &client.addr_len);
		FD_ZERO(&client.set);
		FD_SET(fd, &client.set);
		ft_vector_add(server->clients, &client);
		ft_printf("client added\n");
	}
}

void	run_server_tcp(t_server *server)
{
	char	*line;
	int		r;

	while (1)
	{
		get_new_clients(server);
		while (is_input_waiting(0, server->timeout))
		{
			ft_get_next_line(0, &line);
			ft_putendl(line);
			free(line);
		}
	}
}

void	run_server_udp(t_server *server)
{
	(void)server;
	error(-1, 1, "udp not implemented, dabisous <3");
}

void	run_server(t_server *server)
{
	if (server->protocol == TCP)
		run_server_tcp(server);
	else
		run_server_udp(server);
}

void	start_server(t_server *server)
{
	struct sockaddr_in	addr;

	if (server->protocol == TCP)
	{
		if ((server->socket = socket(AF_INET, server->protocol, 0)) < 0)
			error(0, 1, NULL);
		addr.sin_family = AF_INET;
		addr.sin_port = htons(server->port);
		addr.sin_addr.s_addr = INADDR_ANY;
		if (bind(server->socket, (void*)&addr, sizeof(addr)) < 0 ||
			listen(server->socket, server->queue_max) < 0)
			error(0, 1, NULL);
	}
}
