/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 19:10:08 by pribault          #+#    #+#             */
/*   Updated: 2018/02/02 21:36:36 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	get_default(char *s, t_client *client)
{
	if (!client->address)
		get_address(&s, 1, client);
	else if (!client->port)
		get_port(&s, 1, client);
	else
		ft_error(2, ERROR_PARAMS_ALREADY_SET, s);
}

void	get_protocol(char **args, int n_params, t_client *client)
{
	(void)n_params;
	if (!ft_strcmp(args[0], "tcp"))
		client->protocol = TCP;
	else if (!ft_strcmp(args[0], "udp"))
		client->protocol = UDP;
	else
		ft_error(2, ERROR_INVALID_PROTOCOL, args[0]);
}

void	get_timeout(char **args, int n_params, t_client *client)
{
	(void)n_params;
	server_set_timeout(client->server,
	(struct timeval){ft_atou(args[0]), ft_atou(args[1])});
}
