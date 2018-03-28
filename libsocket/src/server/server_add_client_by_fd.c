/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_add_client_by_fd.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 09:50:47 by pribault          #+#    #+#             */
/*   Updated: 2018/03/28 13:22:49 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	server_add_client_by_fd(t_server *server, int fd)
{
	t_client	client;

	ft_bzero(&client, sizeof(t_client));
	client.fd = fd;
	if (server->client_add)
		server->client_add(server, &client);
	ft_vector_add(&server->clients, &client);
}
