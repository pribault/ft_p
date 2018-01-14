/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 14:19:56 by pribault          #+#    #+#             */
/*   Updated: 2018/01/14 17:17:55 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	get_raw_text(t_server *server, t_client *client, void *msg,
		size_t size)
{
	enqueue_putendl(server, 1, msg, size);
}

void	enter_wait_state(t_client *client, void *data, size_t size)
{
	t_waiting	waiting;

	client->state = STATE_WAITING;
	waiting.header = *(t_header*)data;
	waiting.size = size - sizeof(t_header);
	waiting.data = ft_memdup(data + sizeof(t_header), waiting.size);
	if (!(client->data = ft_memdup(&waiting, sizeof(t_waiting))))
		error(1, 1, NULL);
}

void	wait_state(t_server *server, t_client *client, void *data, size_t size)
{
	t_waiting	*waiting;

	waiting = client->data;
	if (waiting->size + size < waiting->header.size)
	{
		if (!(waiting->data = realloc(waiting->data, waiting->size + size)))
			error(1, 1, NULL);
		ft_memcpy(waiting->data + waiting->size, data, size);
		waiting->size += size;
	}
	else
	{
		if (!(waiting->data = realloc(waiting->data, waiting->header.size)))
			error(1, 1, NULL);
		ft_memcpy(waiting->data + waiting->size, data,
			waiting->header.size - waiting->size);
		waiting->size = waiting->header.size;
		client->state = STATE_IDLE;
		client->data = NULL;
		if (waiting->header.type < TYPE_MAX &&
			g_state_machine[STATE_IDLE][waiting->header.type])
			g_state_machine[STATE_IDLE][waiting->header.type](server, client,
				waiting->data, waiting->header.size);
		free(waiting->data);
		free(waiting);
	}
}

void	treat_message(t_server *server, t_client *client,
		t_header *msg, size_t size)
{
	ft_printf("receiving packet of size %lu\n", size);
	if (client->state == STATE_WAITING)
		wait_state(server, client, msg, size);
	else if (size >= sizeof(t_header))
	{
		if (msg->size <= size - sizeof(t_header))
		{
			if (msg->type < TYPE_MAX)
			{
				if (g_state_machine[client->state][msg->type])
					g_state_machine[client->state][msg->type](server, client,
						(void*)msg + sizeof(t_header), msg->size);
				else
					ft_printf("function NULL\n");
			}
			else
				error(101, 0, NULL);
		}
		else
			enter_wait_state(client, msg, size);
	}
	else if (size != 0)
		error(100, 0, NULL);
	free(msg);
}
