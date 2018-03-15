/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 21:06:13 by pribault          #+#    #+#             */
/*   Updated: 2018/03/11 23:14:39 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int			server_start(t_server *server, t_protocol protocol, char *port)
{
	if (!server || (server->opt & SERVER_RUNNING))
		return (0);
	server->opt |= SERVER_RUNNING;
	server->protocol = protocol;
	server->port = ft_atou(port);
	if (server->clients.n < server->clients_max)
		server_bind(server);
	return (1);
}
