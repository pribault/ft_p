/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 21:06:13 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 11:54:01 by pribault         ###   ########.fr       */
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
	server_bind(server);
	return (1);
}
