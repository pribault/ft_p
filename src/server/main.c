/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 11:04:44 by pribault          #+#    #+#             */
/*   Updated: 2018/01/14 16:55:34 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void		my_exit(void)
{
	t_vector	*vector;
	t_client	*client;
	size_t		i;

	ft_putstr("exiting...\n");
	if (g_global)
	{
		close(g_global->socket);
		i = (size_t)-1;
		vector = g_global->clients;
		while (++i < vector->n)
		{
			client = ft_vector_get(vector, i);
			close(client->fd);
		}
	}
}

void		my_sig(int sig)
{
	exit(sig);
}

t_server	*init_server(void)
{
	static t_server	server;

	ft_bzero(&server, sizeof(t_server));
	server.socket = -1;
	server.protocol = TCP;
	server.port = 4242;
	server.opt = VERBOSE;
	server.queue_max = 10;
	server.timeout = (struct timeval){1, 0};
	if (!(server.clients = ft_vector_new(sizeof(t_client), 0)) ||
		!(server.write_queue = ft_vector_new(sizeof(t_towrite), 0)))
		error(1, 1, NULL);
	return (&server);
}

void		print_config(t_server *server)
{
	ft_printf("\e[0m\e[1mserver starting\e[0m\n");
	ft_printf("\tport: \e[2m%hu\e[0m\n", server->port);
	ft_printf("\tprotocol: \e[2m%s\e[0m\n",
		(server->protocol == TCP) ? "tcp" : "udp");
	ft_printf("\tmax clients: \e[2m%d\e[0m\n", server->queue_max);
	ft_printf("\ttimeout: \e[2m%ds %dusec\e[0m\n",
		server->timeout.tv_sec, server->timeout.tv_usec);
	ft_printf("\tverbose: \e[2m%s\e[0m\n", (server->opt & VERBOSE) ?
		"yes" : "no");
}

int			main(int argc, char **argv)
{
	t_server	*server;

	atexit(&my_exit);
	signal(SIGINT, &my_sig);
	server = init_server();
	get_flags(server, argc, argv);
	if (server->opt & VERBOSE)
		print_config(server);
	start_server(server);
	// g_global = server;
	run_server(server);
	return (0);
}
