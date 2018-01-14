/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 11:04:44 by pribault          #+#    #+#             */
/*   Updated: 2018/01/14 21:40:54 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (connect(client->socket, addr->ai_addr, addr->ai_addrlen) >= 0)
		{
			ft_printf("connected to %s\n",
			inet_ntoa(((struct sockaddr_in *)addr->ai_addr)->sin_addr));
			return (freeaddrinfo(result));
		}
		else
			error(0, 0, NULL);
		addr = addr->ai_next;
	}
	freeaddrinfo(result);
	error(100, 1, client->addr);
}
