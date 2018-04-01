/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_poll_events.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 10:31:22 by pribault          #+#    #+#             */
/*   Updated: 2018/03/29 16:43:08 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	server_add_clients_to_set(fd_set *set, fd_set *err_set,
			t_vector *clients, int *fd_max)
{
	t_client	*client;
	size_t		i;

	i = (size_t)clients->n;
	while (--i != (size_t)-1)
	{
		if ((client = ft_vector_get(clients, i)))
		{
			if (!FD_ISSET(client->fd, set) ||
				!FD_ISSET(client->fd, err_set))
			{
				if (client->fd > *fd_max)
					*fd_max = client->fd;
				FD_SET(client->fd, set);
				FD_SET(client->fd, err_set);
			}
		}
	}
}

static void	server_add_write_request_to_set(fd_set *set, t_circ_buffer *queue,
			int *fd_max)
{
	t_towrite	*towrite;
	size_t		i;

	i = (size_t)-1;
	while ((towrite = ft_circ_buffer_get(queue, ++i)))
	{
		if (towrite->client.fd > *fd_max)
			*fd_max = towrite->client.fd;
		FD_SET(towrite->client.fd, set);
	}
}

static void	set_sets(t_server *server, fd_set *set, int *fd_max)
{
	FD_ZERO(&set[0]);
	FD_ZERO(&set[1]);
	FD_ZERO(&set[2]);
	FD_SET(server->sockfd, &set[0]);
	FD_SET(server->sockfd, &set[2]);
	*fd_max = server->sockfd;
	server_add_clients_to_set(&set[0], &set[2], &server->clients, fd_max);
	server_add_write_request_to_set(&set[1], &server->write_queue, fd_max);
}

void		server_poll_events(t_server *server)
{
	struct timeval	time;
	fd_set			set[3];
	int				fd_max;
	int				ret;

	fd_max = -42;
	set_sets(server, (fd_set*)&set, &fd_max);
	time = server->timeout;
	if ((ret = select(fd_max + 1, &set[0], &set[1], &set[2],
		&time)) <= 0)
		return ;
	if (FD_ISSET(server->sockfd, &set[0]))
	{
		if (server->protocol == TCP)
			server_add_incoming_client(server, &ret);
		else if (server->protocol == UDP)
			server_get_incoming_message(server, &ret);
	}
	if (FD_ISSET(server->sockfd, &set[2]) && server->server_excpt)
		server->server_excpt(server);
	server_manage_incoming_messages(server, &set[0], &set[2], &ret);
	server_manage_write_requests(server, &set[1], &ret);
}
