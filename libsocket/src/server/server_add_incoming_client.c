/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_add_incoming_client.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 17:10:47 by pribault          #+#    #+#             */
/*   Updated: 2018/03/28 11:29:58 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	server_add_incoming_client(t_server *server, int *n_evts)
{
	t_client	client;

	ft_bzero(&client, sizeof(t_client));
	client.addr_len = sizeof(struct sockaddr);
	if ((*n_evts) < 1 ||
		(client.fd = accept(server->sockfd, &client.addr,
		&client.addr_len)) < 0)
		return ;
	(*n_evts)--;
	if (server->client_add)
		server->client_add(server, &client);
	ft_vector_add(&server->clients, &client);
}
