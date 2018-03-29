/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 16:17:46 by pribault          #+#    #+#             */
/*   Updated: 2018/03/28 09:01:05 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	get_root(t_serv *server, char **args, int n_params)
{
	DIR	*dir;

	(void)n_params;
	ft_printf("%s\n", args[0]);
	if (!(dir = opendir(args[0])))
		ft_error(2, ERROR_INVALID_ROOT, args[0]);
	else
	{
		free(server->root);
		server->root = args[0];
		closedir(dir);
	}
}

void	get_protocol(t_serv *server, char **args, int n_params)
{
	(void)n_params;
	if (!ft_strcmp(args[0], "tcp"))
		server->protocol = TCP;
	else if (!ft_strcmp(args[0], "udp"))
		server->protocol = UDP;
	else
		ft_error(2, ERROR_INVALID_PROTOCOL, args[0]);
}

void	get_domain(t_serv *server, char **args, int n_params)
{
	(void)n_params;
	if (!ft_strcmp(args[0], "ipv4"))
		server->domain = IPV4;
	else if (!ft_strcmp(args[0], "ipv6"))
		server->domain = IPV6;
	else
		ft_error(2, ERROR_INVALID_DOMAIN, args[0]);
}

void	get_max(t_serv *server, char **args, int n_params)
{
	(void)n_params;
	server_set_queue_max(server->server, atoi(args[0]));
}

void	get_timeout(t_serv *server, char **args, int n_params)
{
	(void)n_params;
	(void)args;
	(void)server;
	// server_set_timeout(server->server,
	// (struct timeval){ft_atou(args[0]), ft_atou(args[1])});
}
