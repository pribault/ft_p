/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 14:38:58 by pribault          #+#    #+#             */
/*   Updated: 2018/02/02 16:13:55 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static t_short_flag	g_short_flags[] =
{
	{'h', (void*)&print_usage},
	{'v', (void*)&set_verbose},
	{0, NULL}
};

static t_long_flag	g_long_flags[] =
{
	{"help", 0, {}, (void*)&print_usage},
	{"port", 1, {PARAM_UNSIGNED}, (void*)&get_port},
	{"protocol", 1, {PARAM_STR}, (void*)&get_protocol},
	{"max", 1, {PARAM_INTEGER}, (void*)&get_max},
	{"timeout", 2, {PARAM_UNSIGNED, PARAM_UNSIGNED}, (void*)&get_timeout},
	{NULL, 0, {}, NULL}
};

static t_error	g_errors[] =
{
	{ERROR_NOT_IN_PORT_RANGE, "'%s' is not a valid port number [0;65535]", 0},
	{ERROR_PORT_ALREADY_SET, "'%s' port already set", 0},
	{ERROR_INVALID_PROTOCOL, "invalid protocol '%s', allowed: tcp/udp", 0},
	{ERROR_NO_PORT_SET, "please specify a port", ERROR_EXIT},
	{0, NULL, 0}
};

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
	ft_add_errors((t_error*)&g_errors);
	ft_bzero(server, sizeof(t_server));
	server->env = env;
	server->protocol = TCP;
	if (!(server->server = server_new()))
		return (ft_error(2, ERROR_ALLOCATION, NULL));
	if (!(server->root = ft_getenv(env, "PWD")))
		return (ft_error(2, ERROR_CUSTOM, "cannot find PWD in environnement"));
	server_set_callback(server->server, SERVER_CLIENT_ADD_CB, &add_client);
	server_set_callback(server->server, SERVER_CLIENT_DEL_CB, &del_client);
	server_set_callback(server->server, SERVER_MSG_RECV_CB, &msg_recv);
	server_set_callback(server->server, SERVER_MSG_SEND_CB, &msg_send);
	server_attach_data(server->server, server);
	server_add_client_by_fd(server->server, 0);
	ft_get_flags(argc, argv, ft_get_flag_array((t_short_flag*)&g_short_flags,
	(t_long_flag*)&g_long_flags, (void*)&get_default), server);
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
		ft_error(2, ERROR_NO_PORT_SET, NULL);
	}
	server_start(server.server, server.protocol, server.port);
	while (1)
		server_poll_events(server.server);
	return (0);
}
