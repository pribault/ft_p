#include "client.h"

void	connect_to_server(t_client *client)
{
	struct addrinfo	*result;
	struct addrinfo	*addr;
	struct addrinfo	hints;

	ft_bzero(&hints, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = client->protocol;
	if (getaddrinfo(client->addr, client->service, &hints, &result) != 0 ||
		(client->socket = socket(AF_INET, client->protocol, 0)) < 0)
		error(0, 1, NULL);
	addr = result;
	while (addr)
	{
		ft_memdump(addr->ai_addr, addr->ai_addrlen);
		if (connect(client->socket, addr->ai_addr, addr->ai_addrlen) >= 0)
			return ;
		else
			error(0, 0, NULL);
		addr = addr->ai_next;
	}
	error(100, 1, client->addr);
}
