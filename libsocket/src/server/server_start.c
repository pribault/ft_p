/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 21:06:13 by pribault          #+#    #+#             */
/*   Updated: 2018/03/28 11:36:28 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"


static int	server_bind_tcp(t_server *server)
{
	if (listen(server->sockfd, server->queue_max) < 0)
		return (0);
	return (1);
}

static int	server_bind_udp(t_server *server)
{
	(void)server;
	return (1);
}

static int	server_bind(t_server *server)
{
	struct sockaddr_in	addr;
	int					n;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(server->port);
	addr.sin_addr.s_addr = INADDR_ANY;
	n = 1;
	if ((server->sockfd = socket(AF_INET, server->protocol, 0)) < 0 ||
		setsockopt(server->sockfd, SOL_SOCKET, SO_REUSEADDR, &n,
		sizeof(int)) < 0 ||
		bind(server->sockfd, (void*)&addr, sizeof(struct sockaddr_in)) < 0)
		return (0);
	if (server->protocol == TCP)
		return (server_bind_tcp(server));
	else if (server->protocol == UDP)
		return (server_bind_udp(server));
	else
		return (0);
}

int			server_start(t_server *server, char *port)
{
	if ((server->opt & SERVER_RUNNING))
		return (0);
	server->opt |= SERVER_RUNNING;
	server->port = ft_atou(port);
	return (server_bind(server));
}
