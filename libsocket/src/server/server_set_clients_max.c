/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_set_clients_max.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 14:36:53 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 11:58:20 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	server_set_clients_max(t_server *server, size_t max)
{
	if (!server)
		return ;
	server->clients_max = max;
	if (!(server->opt & SERVER_BIND))
	{
		if (server->clients->n < max)
			server_bind(server);
	}
	else
	{
		if (server->clients->n >= max)
			server_unbind(server);
	}
}
