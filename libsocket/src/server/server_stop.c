/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_stop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 21:20:08 by pribault          #+#    #+#             */
/*   Updated: 2018/03/29 16:03:11 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void		server_stop(t_server *server)
{
	t_client	*client;
	t_towrite	*towrite;
	size_t		i;

	if (!(server->opt & SERVER_RUNNING))
		return ;
	server->opt &= ~SERVER_RUNNING;
	while ((towrite = ft_circ_buffer_dequeue(&server->write_queue)))
		free(towrite->data.ptr);
	i = (size_t)-1;
	if (server->protocol == TCP)
		while (++i < server->clients.n)
			if ((client = ft_vector_get(&server->clients, i)))
				close(client->fd);
	ft_vector_resize(&server->clients, 0);
	close(server->sockfd);
	return ;
}
