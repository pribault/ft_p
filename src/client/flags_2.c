/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 19:10:08 by pribault          #+#    #+#             */
/*   Updated: 2018/03/29 13:04:43 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	get_default(char *s, t_cli *client)
{
	if (!client->address)
		get_address(client, &s, 1);
	else if (!client->port)
		get_port(client, &s, 1);
	else
		ft_error(2, ERROR_PARAMS_ALREADY_SET, s);
}

void	get_protocol(t_cli *client, char **args, int n_params)
{
	(void)n_params;
	if (!ft_strcmp(args[0], "tcp"))
		client->protocol = TCP;
	else if (!ft_strcmp(args[0], "udp"))
		client->protocol = UDP;
	else
		ft_error(2, ERROR_INVALID_PROTOCOL, args[0]);
}

void	get_timeout(t_cli *client, char **args, int n_params)
{
	(void)n_params;
	(void)args;
	(void)client;
	// server_set_timeout(client->server,
	// (struct timeval){ft_atou(args[0]), ft_atou(args[1])});
}
