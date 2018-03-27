/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 18:41:38 by pribault          #+#    #+#             */
/*   Updated: 2018/02/02 21:36:33 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	print_usage(void)
{
	ft_putchar('\n');
	ft_putstr("\e[0m\e[3m\e[1m./client <address> <port> <options>\e[0m\n");
	ft_putstr(" \e[2mavailable options:\e[0m\n");
	ft_putstr("  --\e[4mhelp\e[0m or -h: \e[2mprint usage\e[0m\n");
	ft_putstr("  --\e[4mverbose\e[0m or -v: \e[2mturn verbose on/off\e[0m\n");
	ft_putstr("  --\e[4mprotocol\e[0m: \e[2mtcp/udp\e[0m\n");
	ft_putstr("  --\e[4mtimeout\e[0m: \e[2m<seconds> <nano-seconds>");
	ft_putstr("<n micro seconds>\e[0m\n");
	ft_putchar('\n');
}

void	set_verbose(t_cli *client)
{
	client->opt ^= OPT_VERBOSE;
}

void	set_long_verbose(char **args, int n_params, t_cli *client)
{
	(void)args;
	(void)n_params;
	client->opt ^= OPT_VERBOSE;
}

void	get_port(char **args, int n_params, t_cli *client)
{
	unsigned int	n;

	(void)n_params;
	if (!ft_isunsigned(args[0]))
		return (ft_error(2, ERROR_UNSIGNED, args[0]));
	if (client->port)
		return (ft_error(2, ERROR_PORT_ALREADY_SET, args[0]));
	n = ft_atou(args[0]);
	if (n > 65535)
		ft_error(2, ERROR_NOT_IN_PORT_RANGE, args[0]);
	else
		client->port = args[0];
}

void	get_address(char **args, int n_params, t_cli *client)
{
	(void)n_params;
	if (client->address)
		return (ft_error(2, ERROR_ADDRESS_ALREADY_SET, args[0]));
	client->address = args[0];
}
