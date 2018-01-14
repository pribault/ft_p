/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 15:53:16 by pribault          #+#    #+#             */
/*   Updated: 2018/01/14 21:14:50 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	write_output(t_server *server, int *n)
{
	t_towrite	*data;
	t_vector	*vector;
	size_t		i;

	i = (size_t)-1;
	vector = server->write_queue;
	while (*n && ++i != vector->n)
	{
		data = ft_vector_get(vector, i);
		if (FD_ISSET(data->fd, &server->out))
		{
			if (write(data->fd, data->data, data->size) < 0)
				error(0, 0, NULL);
			free(data->data);
			ft_vector_del_one(vector, i--);
			(*n)--;
		}
	}
}

void	set_output(t_server *server)
{
	t_towrite	*data;
	t_vector	*vector;
	size_t		i;

	i = (size_t)-1;
	vector = server->write_queue;
	FD_ZERO(&server->out);
	while (++i < vector->n)
	{
		data = ft_vector_get(vector, i);
		FD_SET(data->fd, &server->out);
		if (data->fd > server->io_max)
			server->io_max = data->fd;
	}
}

void	enqueue_putendl(t_server *server, int fd, char *s, size_t len)
{
	s[len] = '\n';
	enqueue_write(server, fd, s, len + 1);
	s[len] = '\0';
}

void	enqueue_write(t_server *server, int fd, void *data, size_t size)
{
	t_towrite	towrite;

	towrite.fd = fd;
	if (!(towrite.data = ft_memdup(data, size)))
		return (error(1, 0, NULL));
	towrite.size = size;
	ft_vector_add(server->write_queue, &towrite);
}
