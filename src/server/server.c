/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 11:04:44 by pribault          #+#    #+#             */
/*   Updated: 2018/01/14 13:46:14 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	run_server_tcp(t_server *server)
{
	int				r;

	while (1)
	{
		server->io_max = 0;
		set_input(server);
		set_output(server);
		if ((r = select(server->io_max + 1, &server->in, &server->out, NULL,
			&server->timeout)) < 0)
			error(0, 0, NULL);
		else if (r > 0)
		{
			read_from_terminal(server, &r);
			read_from_socket(server, &r);
			read_input(server, &r);
			write_output(server, &r);
		}
	}
}

void	run_server_udp(t_server *server)
{
	(void)server;
	error(-1, 1, "udp not implemented, dabisous <3");
}

void	run_server(t_server *server)
{
	if (server->protocol == TCP)
		run_server_tcp(server);
	else
		run_server_udp(server);
}

void	start_server(t_server *server)
{
	struct sockaddr_in	addr;
	int					n;

	if (server->protocol == TCP)
	{
		if ((server->socket = socket(AF_INET, server->protocol, 0)) < 0)
			error(0, 1, NULL);
		addr.sin_family = AF_INET;
		addr.sin_port = htons(server->port);
		addr.sin_addr.s_addr = INADDR_ANY;
		n = 1;
		if (setsockopt(server->socket, SOL_SOCKET, SO_REUSEADDR, &n,
			sizeof(int)) < 0 ||
			bind(server->socket, (void*)&addr, sizeof(addr)) < 0 ||
			listen(server->socket, server->queue_max) < 0)
			error(0, 1, NULL);
	}
}
