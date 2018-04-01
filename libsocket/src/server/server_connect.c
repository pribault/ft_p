/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_connect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 16:33:12 by pribault          #+#    #+#             */
/*   Updated: 2018/03/29 18:07:34 by pribault         ###   ########.fr       */
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
			ft_memcpy(&client->addr, addr->ai_addr, addr->ai_addrlen);
			client->addr_len = addr->ai_addrlen;
			client->write_type = WRITE_BY_ADDR;
			ft_vector_add(&server->clients, client);
			if (server->client_add)
				server->client_add(server, ft_vector_get(&server->clients,
				server->clients.n - 1));
			freeaddrinfo(result);
			return (1);
		}
		addr = addr->ai_next;
	}
	freeaddrinfo(result);
	return (0);
}

int			server_connect(t_server *server, t_method method, char *address,
			char *port)
{
	t_client		client;
	struct addrinfo	hints;
	struct addrinfo	*result;

	ft_bzero(&hints, sizeof(struct addrinfo));
	ft_bzero(&client, sizeof(t_client));
	hints.ai_family = method.domain;
	hints.ai_socktype = method.protocol;
	result = NULL;
	if (getaddrinfo(address, port, &hints, &result) != 0 ||
		(client.fd = socket(method.domain, method.protocol, 0)) < 0)
	{
		if (result)
			freeaddrinfo(result);
		return (0);
	}
	return (iter_on_addresses(server, &client, result));
}
