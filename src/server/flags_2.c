/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 16:17:46 by pribault          #+#    #+#             */
/*   Updated: 2018/02/03 18:24:45 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	get_root(char **args, int n_params, t_server *server)
{
	DIR	*dir;

	(void)n_params;
	if (!(dir = opendir(args[0])))
		ft_error(2, ERROR_INVALID_ROOT, args[0]);
	else
	{
		free(server->root);
		server->root = args[0];
		closedir(dir);
	}
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
