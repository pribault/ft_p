/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 15:12:21 by pribault          #+#    #+#             */
/*   Updated: 2018/03/28 09:04:21 by pribault         ###   ########.fr       */
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
	ft_putstr("  --\e[4mverbose\e[0m or -v: \e[2mturn verbose on/off\e[0m\n");
	ft_putstr("  --\e[4mprotocol\e[0m: \e[2mtcp/udp\e[0m\n");
	ft_putstr("  --\e[4mdomain\e[0m: \e[2mipv4/ipv6\e[0m\n");
	ft_putstr("  --\e[4mmax\e[0m: \e[2m<n>\e[0m\n");
	ft_putstr("  --\e[4mtimeout\e[0m: \e[2m<seconds> <nano-seconds>");
	ft_putstr("<n micro seconds>\e[0m\n");
	ft_putchar('\n');
	printed = FT_TRUE;
}

void	set_verbose(t_serv *server)
{
	server->opt ^= OPT_VERBOSE;
}

void	set_long_verbose(t_serv *server, char **args, int n_params)
{
	(void)args;
	(void)n_params;
	server->opt ^= OPT_VERBOSE;
}

void	get_default(char *s, t_serv *server)
{
	get_port(server, &s, 1);
}

void	get_port(t_serv *server, char **args, int n_params)
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
