/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_manage_incoming_messages.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 17:18:48 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 13:48:55 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	server_get_client_message(t_server *server, t_client *client)
{
	static char		buffer[READ_BUFFER_SIZE];
	int				ret;
	static t_msg	msg;

	if ((ret = read(client->fd, &buffer, READ_BUFFER_SIZE)) > 0)
	{
		if (server->msg_recv)
		{
			msg.ptr = &buffer;
			msg.size = ret;
			server->msg_recv(server, client, &msg);
		}
	}
	else if (!ret)
		server_remove_client(server, client);
}

void		server_manage_incoming_messages(t_server *server, fd_set *set,
			fd_set *err_set, int *n_evts)
{
	t_vector	*vector;
	t_client	*client;
	size_t		i;

	if ((*n_evts) < 1 || !(vector = &server->clients))
		return ;
	i = vector->n;
	while (--i != (size_t)-1 && (*n_evts))
	{
		if ((client = ft_vector_get(vector, i)))
		{
			if (FD_ISSET(client->fd, err_set))
			{
				server_remove_client(server, client);
				(*n_evts)--;
			}
			else if (FD_ISSET(client->fd, set))
			{
				server_get_client_message(server, client);
				(*n_evts)--;
			}
		}
	}
}
