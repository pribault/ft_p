/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_connect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 16:33:12 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 11:16:54 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int	iter_on_addresses(t_server *server, t_client *client,
			struct addrinfo *result)
{
	struct addrinfo	*addr;

	addr = result;
	while (addr)
	{
		if (connect(client->fd, addr->ai_addr, addr->ai_addrlen) >= 0)
		{
			client->addr = *addr->ai_addr;
			client->addr_len = addr->ai_addrlen;
			ft_vector_add(server->clients, client);
			if (server->client_add)
				server->client_add(server, client);
			freeaddrinfo(result);
			return (1);
		}
		addr = addr->ai_next;
	}
	freeaddrinfo(result);
	return (0);
}

int			server_connect(t_server *server, char *address, char *port)
{
	t_client		client;
	struct addrinfo	hints;
	struct addrinfo	*result;

	if (!server || !address || !port ||
		server->clients->n >= server->clients_max)
		return (0);
	ft_bzero(&hints, sizeof(struct addrinfo));
	ft_bzero(&client, sizeof(t_client));
	hints.ai_family = AF_INET;
	hints.ai_socktype = server->protocol;
	result = NULL;
	if (getaddrinfo(address, port, &hints, &result) != 0 ||
		(client.fd = socket(AF_INET, server->protocol, 0)) < 0)
	{
		if (result)
			freeaddrinfo(result);
		return (0);
	}
	return (iter_on_addresses(server, &client, result));
}
