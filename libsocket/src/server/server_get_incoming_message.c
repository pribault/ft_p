/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_get_incoming_message.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 16:43:32 by pribault          #+#    #+#             */
/*   Updated: 2018/03/29 17:38:39 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	server_add_client_udp(t_server *server, t_client *client)
{
	client->write_type = WRITE_BY_ADDR;
	ft_vector_add(&server->clients, client);
	server->client_add(server, ft_vector_get(&server->clients,
	server->clients.n - 1));
}

#include <errno.h>
void		server_get_incoming_message(t_server *server, int *n_evts)
{
	char		buffer[READ_BUFFER_SIZE];
	t_client	client;
	t_client	*new;
	t_msg		msg;
	int			ret;

	client.fd = server->sockfd;
	client.addr_len = sizeof(struct sockaddr_storage);
	if ((ret = recvfrom(server->sockfd, &buffer, READ_BUFFER_SIZE,
		0, (void*)&client.addr, &client.addr_len)) == -1)
		return ;
	(*n_evts)--;
	if (!(new = server_find_client_by_address(server, &client.addr)) &&
		server->client_add)
		server_add_client_udp(server, &client);
	if (server->msg_recv)
	{
		msg = (t_msg){&buffer, ret};
		server->msg_recv(server, ft_vector_get(&server->clients,
		server->clients.n - 1), &msg);
	}
}
