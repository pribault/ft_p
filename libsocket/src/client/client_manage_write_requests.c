/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_manage_write_requests.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 13:46:53 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 13:56:40 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	client_manage_write_requests(t_client *client, fd_set *set,
		int *n_evts)
{
	t_towrite	*towrite;
	t_vector	*vector;
	size_t		i;

	if ((*n_evts) < 1 || !(vector = client->write_queue))
		return ;
	i = vector->n;
	while (--i != (size_t)-1 && (*n_evts))
	{
		if ((towrite = ft_vector_get(vector, i)) &&
			FD_ISSET(towrite->fd, set))
		{
			if (write(towrite->fd, towrite->data.ptr,
				towrite->data.size) < 0)
				return ;
			ft_vector_del_one(vector, i);
			if (client->msg_send)
				client->msg_send(client, towrite->fd, &towrite->data);
			(*n_evts)--;
		}
	}
}
