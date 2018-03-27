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
	t_towrite		*towrite;
	t_circ_buffer	*buffer;
	uint64_t		size;
	uint64_t		i;

	if ((*n_evts) < 1 || !(buffer = &client->write_queue))
		return ;
	i = (uint64_t)-1;
	size = ft_circ_buffer_get_size(buffer);
	while (++i < size &&
		(towrite = ft_circ_buffer_dequeue(buffer)))
		if (FD_ISSET(towrite->fd, set))
		{
			FD_CLR(towrite->fd, set);
			if (write(towrite->fd, towrite->data.ptr,
				towrite->data.size) < 0)
				return (ft_circ_buffer_enqueue(buffer, towrite));
			if (client->msg_send)
				client->msg_send(client, towrite->fd, &towrite->data);
			(*n_evts)--;
		}
		else
			ft_circ_buffer_enqueue(buffer, towrite);
}
