/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 14:38:53 by pribault          #+#    #+#             */
/*   Updated: 2018/03/29 13:09:33 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static t_short_flag	g_short_flags[] =
{
	{'h', (void*)&print_usage},
	{'v', (void*)&set_verbose},
	{0, NULL}
};

static t_long_flag	g_long_flags[] =
{
	{"help", 0, {0}, (void*)&print_usage},
	{"address", 1, {PARAM_STR}, (void*)&get_address},
	{"port", 1, {PARAM_UNSIGNED}, (void*)&get_port},
	{"protocol", 1, {PARAM_STR}, (void*)&get_protocol},
	{"domain", 1, {PARAM_STR}, (void*)&get_domain},
	{"timeout", 1, {PARAM_UNSIGNED, PARAM_UNSIGNED}, (void*)&get_timeout},
	{NULL, 0, {0}, NULL}
};

static t_error	g_errors[] =
{
	{ERROR_NOT_IN_PORT_RANGE, "'%s' is not a valid port number [0;65535]", 0},
	{ERROR_ADDRESS_ALREADY_SET, "'%s' address already set", 0},
	{ERROR_PORT_ALREADY_SET, "'%s' port already set", 0},
	{ERROR_PARAMS_ALREADY_SET, "'%s' address and port already set", 0},
	{ERROR_INVALID_PROTOCOL, "invalid protocol '%s', allowed: tcp/udp", 0},
	{ERROR_INVALID_DOMAIN, "invalid domain '%s', allowed: ipv4/ipv6", 0},
	{ERROR_NO_ADDRESS_SET, "please specify an address", ERROR_EXIT},
	{ERROR_NO_PORT_SET, "please specify a port", ERROR_EXIT},
	{ERROR_CANNOT_CONNECT, "cannot connect to '%s'", ERROR_EXIT},
	{ERROR_MSG_TOO_SMALL, "message too small, ignoring", 0},
	{ERROR_UNEXPECTED_MSG, "unexpected message received", 0},
	{ERROR_UNKNOWN_MSG_TYPE, "unkown message type %ld", 0},
	{ERROR_EXPECTING_STR, "%ld received, expecting string", 0},
	{ERROR_LS_PARAMS, "ls cannot take more than one parameter", 0},
	{ERROR_CD_PARAMS, "cd cannot take more than one parameter", 0},
	{ERROR_PWD_PARAMS, "pwd don't take any parameter", 0},
	{ERROR_PUT_PARAMS, "put take only one parameter", 0},
	{ERROR_GET_PARAMS, "get take only one parameter", 0},
	{ERROR_EXIT_PARAMS, "exit don't take any parameter", 0},
	{ERROR_UNKNOWN_COMMAND, "unknown command '%s'", 0},
	{ERROR_FILE_ALREADY_EXIST, "file '%s' already exist", 0},
	{ERROR_FILE_NAME_TOO_LONG, "file name '%s' too long", 0},
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

void	client_init(t_cli *client, int argc, char **argv, char **env)
{
	ft_add_errors((t_error*)&g_errors);
	ft_bzero(client, sizeof(t_cli));
	client->env = env;
	client->protocol = TCP;
	client->domain = IPV4;
	client->opt = 0;
	client->state = STATE_NONE;
	ft_get_flags(argc, argv, ft_get_flag_array((t_short_flag*)&g_short_flags,
	(t_long_flag*)&g_long_flags, (void*)&get_default), client);
	if (!(client->server = server_new()))
		return (ft_error(2, ERROR_ALLOCATION, NULL));
	server_attach_data(client->server, client);
	server_set_callback(client->server, SERVER_CLIENT_ADD_CB, &add_client);
	server_set_callback(client->server, SERVER_CLIENT_DEL_CB, &del_client);
	server_set_callback(client->server, SERVER_MSG_RECV_CB, &msg_recv);
	server_set_callback(client->server, SERVER_MSG_SEND_CB, &msg_send);
	server_set_callback(client->server, SERVER_MSG_TRASH_CB, &msg_trash);
	// server_set_clients_max(client->server, 2);
	server_add_client_by_fd(client->server, 0);
}

int		main(int argc, char **argv, char **env)
{
	t_cli	client;

	setenv("MALLOC_DEBUG", "1", 1);
	atexit(&my_exit);
	signal(SIGINT, &my_sig);
	client_init(&client, argc, argv, env);
	if (!client.address)
		ft_error(2, ERROR_NO_ADDRESS_SET, NULL);
	if (!client.port)
		ft_error(2, ERROR_NO_PORT_SET, NULL);
	if (!server_connect(client.server, (t_method){client.protocol, IPV4},
		client.address, client.port))
		ft_error(2, ERROR_CANNOT_CONNECT, client.address);
	// server_set_clients_max(client.server, 0);
	while (1)
		server_poll_events(client.server);
	return (0);
}
