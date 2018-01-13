/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 18:18:05 by pribault          #+#    #+#             */
/*   Updated: 2018/01/13 19:40:39 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	write_output(t_client *client, int *n)
{
	t_towrite	*data;
	t_vector	*vector;
	size_t		i;
	int			r;

	i = (size_t)-1;
	vector = client->write_queue;
	while (*n && ++i < vector->n)
	{
		data = ft_vector_get(vector, i);
		if (FD_ISSET(data->fd, &client->out))
		{
			if ((r = write(data->fd, data->data, data->size)) < 0)
				error(0, 0, NULL);
			else
				ft_printf("write: %d\n", r);
			free(data->data);
			ft_vector_del_one(vector, i--);
			(*n)--;
		}
	}
}

void	enqueue_write(t_client *client, int fd, void *data, size_t size)
{
	t_towrite	towrite;

	towrite.fd = fd;
	towrite.data = ft_memdup(data, size);
	towrite.size = size;
	ft_vector_add(client->write_queue, &towrite);
}
