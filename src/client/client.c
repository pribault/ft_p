/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 14:38:53 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 19:06:10 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	my_exit(void)
{
	ft_printf("exiting...\n");
}

void	my_sig(int sig)
{
	ft_printf("receiving signal %d\n", sig);
	exit(1);
}

void	client_init(t_client *client, int argc, char **argv, char **env)
{
	ft_bzero(client, sizeof(t_client));
	client->env = env;
	if (!(client->server = server_new()))
		return (error(1, 1, NULL));
	server_set_callback(client->server, SERVER_CLIENT_ADD_CB, &add_client);
	server_set_callback(client->server, SERVER_CLIENT_DEL_CB, &del_client);
	server_set_callback(client->server, SERVER_MSG_RECV_CB, &msg_recv);
	server_set_callback(client->server, SERVER_MSG_SEND_CB, &msg_send);
	server_set_clients_max(client->server, 2);
	server_add_client_by_fd(client->server, 0);
	server_attach_data(client->server, client);
	get_flags(client, argc, argv);
}

int		main(int argc, char **argv, char **env)
{
	t_client	client;

	atexit(&my_exit);
	signal(SIGINT, &my_sig);
	client_init(&client, argc, argv, env);
	if (!client.address || !client.port)
	{
		print_usage();
		return (1);
	}
	if (!server_connect(client.server, TCP, client.address, client.port))
		error(4, 1, &client);
	while (1)
		server_poll_events(client.server);
	return (0);
}
