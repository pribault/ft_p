#include "server.h"

void	run_server_tcp(t_server *server)
{
	(void)server;
	while (1)
	{
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
		if ((server->socket = socket(AF_INET, server->protocol |
			SOCK_NONBLOCK, 0)) < 0)
			error(0, 1, NULL);
		addr.sin_family = AF_INET;
		addr.sin_port = htons(server->port);
		addr.sin_addr.s_addr = INADDR_ANY;
		if (bind(server->socket, (void*)&addr, sizeof(addr)) < 0 ||
			listen(server->socket, server->queue_max) < 0)
			error(0, 1, NULL);
	}
}
