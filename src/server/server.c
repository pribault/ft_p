/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 14:38:58 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 17:05:12 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	my_exit(void)
{
	ft_printf("exiting...\n");
}

void	my_sig(int sig)
{
	ft_printf("receiving signal %d\n", sig);
	exit(1);
}

void	server_init(t_server *server, int argc, char **argv, char **env)
{
	ft_bzero(server, sizeof(t_server));
	server->env = env;
	if (!(server->server = server_new()))
		return (error(1, 1, NULL));
	server_set_callback(server->server, SERVER_CLIENT_ADD_CB, &add_client);
	server_set_callback(server->server, SERVER_CLIENT_DEL_CB, &del_client);
	server_set_callback(server->server, SERVER_MSG_RECV_CB, &msg_recv);
	server_set_callback(server->server, SERVER_MSG_SEND_CB, &msg_send);
	server_add_client_by_fd(server->server, 0);
	server_attach_data(server->server, server);
	get_flags(server, argc, argv);
}

int		main(int argc, char **argv, char **env)
{
	t_server	server;

	atexit(&my_exit);
	signal(SIGINT, &my_sig);
	server_init(&server, argc, argv, env);
	if (!server.port)
	{
		print_usage();
		return (1);
	}
	server_start(server.server, TCP, server.port);
	while (1)
		server_poll_events(server.server);
	return (0);
}
