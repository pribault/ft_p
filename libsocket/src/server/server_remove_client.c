/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_remove_client.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 19:22:39 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 11:53:41 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	server_remove_client_by_fd(t_vector *vector,
			t_client *client)
{
	t_client	*tmp;
	size_t		i;

	i = vector->n;
	while (--i != (size_t)-1)
	{
		if ((tmp = ft_vector_get(vector, i)) &&
			tmp->fd == client->fd)
		{
			ft_vector_del_one(vector, i);
			return ;
		}
	}
}

void		server_remove_client(t_server *server, t_client *client)
{
	t_vector	*vector;

	if (!server || !(vector = server->clients) || !client)
		return ;
	if (server->client_del)
		server->client_del(server, client);
	close(client->fd);
	if ((void*)client >= vector->ptr &&
		(void*)client < vector->ptr + vector->size)
		ft_vector_del_one(vector, ((void*)client - vector->ptr) /
		vector->type);
	else
		server_remove_client_by_fd(vector, client);
	if (!(server->opt & SERVER_BIND) &&
		server->clients->n < server->clients_max)
		server_bind(server);
}
