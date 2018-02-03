/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_manage_write_requests.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 17:18:05 by pribault          #+#    #+#             */
/*   Updated: 2018/02/03 13:02:46 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	server_manage_write_requests(t_server *server, fd_set *set,
		int *n_evts)
{
	t_towrite	*towrite;
	t_vector	*vector;
	size_t		i;

	if ((*n_evts) < 1 || !(vector = server->write_queue))
		return ;
	i = (size_t)-1;
	while (++i < vector->n && (*n_evts))
	{
		if ((towrite = ft_vector_get(vector, i)) &&
			FD_ISSET(towrite->client.fd, set))
		{
			if (write(towrite->client.fd, towrite->data.ptr,
				towrite->data.size) < 0)
				return ;
			if (server->msg_send)
				server->msg_send(server, &towrite->client, &towrite->data);
			ft_vector_del_one(vector, i--);
			(*n_evts)--;
		}
	}
}
