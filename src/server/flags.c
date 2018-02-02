/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 15:12:21 by pribault          #+#    #+#             */
/*   Updated: 2018/02/02 16:14:46 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	print_usage(void)
{
	static t_bool	printed = FT_FALSE;

	if (printed)
		return ;
	ft_putchar('\n');
	ft_putstr("\e[0m\e[3m\e[1m./server <port> <options>\e[0m\n");
	ft_putstr(" \e[2mavailable options:\e[0m\n");
	ft_putstr("  --\e[4mhelp\e[0m or -h: \e[2mprint usage\e[0m\n");
	ft_putstr("  --\e[4mverbose\e[0m or -v: \e[2mturn verbose mode on\e[0m\n");
	ft_putstr("  --\e[4mprotocol\e[0m: \e[2mtcp/udp\e[0m\n");
	ft_putstr("  --\e[4mmax\e[0m: \e[2m<n>\e[0m\n");
	ft_putstr("  --\e[4mtimeout\e[0m: \e[2m<n second> ");
	ft_putstr("<n micro seconds>\e[0m\n");
	ft_putchar('\n');
	printed = FT_TRUE;
}

void	set_verbose(t_server *server)
{
	server->opt |= OPT_VERBOSE;
}

void	get_default(char *s, t_server *server)
{
	get_port(&s, 1, server);
}

void	get_protocol(char **args, int n_params, t_server *server)
{
	(void)n_params;
	if (!ft_strcmp(args[0], "tcp"))
		server->protocol = TCP;
	else if (!ft_strcmp(args[0], "udp"))
		server->protocol = UDP;
	else
		ft_error(2, ERROR_INVALID_PROTOCOL, args[0]);
}

void	get_port(char **args, int n_params, t_server *server)
{
	unsigned int	n;

	(void)n_params;
	if (!ft_isunsigned(args[0]))
		return (ft_error(2, ERROR_UNSIGNED, args[0]));
	if (server->port)
		return (ft_error(2, ERROR_PORT_ALREADY_SET, args[0]));
	n = ft_atou(args[0]);
	if (n > 65535)
		ft_error(2, ERROR_NOT_IN_PORT_RANGE, args[0]);
	else
		server->port = args[0];
}

void	get_max(char **args, int n_params, t_server *server)
{
	(void)n_params;
	server_set_queue_max(server->server, atoi(args[0]));
}

void	get_timeout(char **args, int n_params, t_server *server)
{
	(void)n_params;
	server_set_timeout(server->server,
	(struct timeval){ft_atou(args[0]), ft_atou(args[1])});
}
