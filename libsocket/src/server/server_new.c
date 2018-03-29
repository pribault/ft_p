/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 20:56:42 by pribault          #+#    #+#             */
/*   Updated: 2018/03/28 12:59:33 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	server_trash_callback(t_server *server, t_towrite *towrite)
{
	if (server->msg_trash)
		server->msg_trash(server, &towrite->client, &towrite->data);
}

t_server	*server_new(void)
{
	t_server	*server;

	if (!(server = (t_server*)malloc(sizeof(t_server))))
		return (NULL);
	ft_bzero(server, sizeof(t_server));
	ft_vector_init(&server->clients, sizeof(t_client));
	ft_circ_buffer_init(&server->write_queue, sizeof(t_towrite),
	CIRCULAR_BUFFER_SIZE);
	ft_circ_buffer_set_trash_callback(&server->write_queue,
	(void*)&server_trash_callback, server);
	server->queue_max = SERVER_DEFAULT_QUEUE_MAX;
	server->timeout = (struct timeval){SERVER_DEFAULT_TIMEOUT_S,
	SERVER_DEFAULT_TIMEOUT_US};
	server->opt = 0;
	return (server);
}
