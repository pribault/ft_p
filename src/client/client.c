/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 11:04:44 by pribault          #+#    #+#             */
/*   Updated: 2018/01/13 19:40:09 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	set_fds(t_client *client)
{
	t_vector	*vector;
	t_towrite	*data;
	size_t		i;

	FD_ZERO(&client->in);
	FD_ZERO(&client->out);
	FD_SET(0, &client->in);
	FD_SET(client->socket, &client->in);
	vector = client->write_queue;
	i = (size_t)-1;
	while (++i < vector->n)
	{
		data = ft_vector_get(vector, i);
		FD_SET(data->fd, &client->out);
	}
}

void	run_client(t_client *client)
{
	int	r;

	while (1)
	{
		set_fds(client);
		if ((r = select(client->socket + 1, &client->in, &client->out, NULL,
			&client->timeout)) < 0)
			error(0, 0, NULL);
		else if (r > 0)
		{
			read_from_terminal(client, &r);
			read_from_socket(client, &r);
			write_output(client, &r);
		}
	}
}
