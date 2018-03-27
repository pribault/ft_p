/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 20:56:42 by pribault          #+#    #+#             */
/*   Updated: 2018/01/20 14:46:01 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_server	*server_new(t_protocol protocol)
{
	t_server	*server;

	if (!(server = (t_server*)malloc(sizeof(t_server))))
		return (NULL);
	ft_bzero(server, sizeof(t_server));
	ft_vector_init(&server->clients, sizeof(t_client));
	ft_circ_buffer_init(&server->write_queue, sizeof(t_towrite),
	CIRCULAR_BUFFER_SIZE);
	server->queue_max = SERVER_DEFAULT_QUEUE_MAX;
	server->timeout = (struct timeval){SERVER_DEFAULT_TIMEOUT_S,
	SERVER_DEFAULT_TIMEOUT_US};
	server->opt = 0;
	server->protocol = protocol;
	return (server);
}
